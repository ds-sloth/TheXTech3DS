#include <stdio.h>
#include <string.h>
#include "3ds-audio-lib.h"
#include <tremor/ivorbisfile.h>
#include <3ds.h>
#include <cstdlib>

volatile SimpleChannel channels[NUM_CHANNELS];
char *audio_buffer = NULL;

LightEvent sound_event;
Thread sound_thread;
volatile bool sound_quit = false;  // Quit flag

void myAudioCallback(void *const nul_) {
    if(sound_quit)
        return;

    LightEvent_Signal(&sound_event);
}

// should only be called by the audio thread if it is running
void closeChannel(volatile SimpleChannel *channel)
{
    if (channel->format == FORMAT_PCM_FILE && channel->data_pointer != NULL)
    {
        fclose((FILE*)channel->data_pointer);
    }
    if (channel->format == FORMAT_OGG_FILE && channel->data_pointer != NULL)
    {
        ov_clear((OggVorbis_File*)channel->data_pointer);
        free(channel->data_pointer);
    }
    channel->data_pointer = nullptr;
}

// returns true on success, false on failure
bool fillBuffer(volatile SimpleChannel *channel, volatile ndspWaveBuf *wavebuf)
{
    if (wavebuf->status != NDSP_WBUF_DONE) return false;
    // load data into wavebuf...
    if (channel->format == FORMAT_PCM_FILE && channel->data_pointer != NULL)
    {
        int32_t *buffer_loc = (int32_t *)wavebuf->data_pcm16; // in 2x16-bit samples
        wavebuf->nsamples = 0;
        size_t samplesToRead = BUFFER_SIZE / sizeof(*buffer_loc);
        while(samplesToRead > 0) {
            // Decode bufferSize samples from opusFile_ into buffer,
            // storing the number of samples that were decoded (or error)
            int samples = fread(buffer_loc, sizeof(*buffer_loc), samplesToRead, (FILE*)channel->data_pointer);
            if(samples == 0) {
                if (channel->loops == 0)
                {
                    closeChannel(channel);
                    break;
                }
                else
                {
                    if (channel->loops > 0)
                        channel->loops -= 1;
                    fseek((FILE*)channel->data_pointer, 44, SEEK_SET);
                }
            }

            wavebuf->nsamples += samples;
            buffer_loc += samples;
            samplesToRead -= samples;
        }
        if (channel->stereo)
        {
            ndspChnWaveBufAdd(channel->channel_id, (ndspWaveBuf*)wavebuf);
            DSP_FlushDataCache(wavebuf->data_pcm16,
                wavebuf->nsamples * sizeof(*buffer_loc));
        }
        else
        {
            wavebuf->nsamples *= 2;
            ndspChnWaveBufAdd(channel->channel_id, (ndspWaveBuf*)wavebuf);
            DSP_FlushDataCache(wavebuf->data_pcm16,
                wavebuf->nsamples / 2 * sizeof(*buffer_loc));
        }
        return true;
    }
    if (channel->format == FORMAT_OGG_FILE && channel->data_pointer != NULL)
    {
        char *buffer_loc = (char *)wavebuf->data_pcm16; // in 2x16-bit samples
        wavebuf->nsamples = 0;
        size_t samplesToRead = BUFFER_SIZE;
        while(samplesToRead > 0) {
            // Decode bufferSize samples from opusFile_ into buffer,
            // storing the number of samples that were decoded (or error)
            int samples = ov_read((OggVorbis_File*)channel->data_pointer, buffer_loc, samplesToRead, nullptr);
            if(samples == 0) {
                if (channel->loops == 0)
                {
                    closeChannel(channel);
                    break;
                }
                else
                {
                    if (channel->loops > 0)
                        channel->loops -= 1;
                    ov_pcm_seek((OggVorbis_File*)channel->data_pointer, 0);
                }
            }

            wavebuf->nsamples += samples;
            buffer_loc += samples;
            samplesToRead -= samples;
        }
        // depends strongly on stereo-ness......
        if (channel->stereo)
        {
            wavebuf->nsamples /= 4;
            ndspChnWaveBufAdd(channel->channel_id, (ndspWaveBuf*)wavebuf);
            DSP_FlushDataCache(wavebuf->data_pcm16,
                wavebuf->nsamples * 4);
        }
        else
        {
            wavebuf->nsamples /= 2;
            ndspChnWaveBufAdd(channel->channel_id, (ndspWaveBuf*)wavebuf);
            DSP_FlushDataCache(wavebuf->data_pcm16,
                wavebuf->nsamples * 2);
        }
        return true;
    }
    return false;
}

void audioThread(void* nul_)
{
    while(!sound_quit)
    {
        for (size_t ci = 0; ci < NUM_CHANNELS; ci++)
        {
            volatile SimpleChannel *channel = &channels[ci];
            if (channel->kill)
            {
                closeChannel(channel);
                ndspChnWaveBufClear(channel->channel_id);

                channel->format = FORMAT_FREE;
                channel->kill = false;
            }
            else if (channel->format != FORMAT_FREE)
            {
                for (size_t wi = 0; wi < NUM_BUFFERS; wi++)
                {
                    ndspWaveBuf *wavebuf = (ndspWaveBuf*) &(channel->wavebufs[wi]);
                    if(wavebuf->status != NDSP_WBUF_DONE) continue;
                    if(!fillBuffer(channel, wavebuf) && !ndspChnIsPlaying(channel->channel_id))
                        channel->format = FORMAT_FREE;
                    // printf("Responding at %llu...\n", osGetTime());
                }
            }
        }
        LightEvent_Wait(&sound_event);
    }
}

int loadWaveFile(FILE* f, uint16_t* nChannels, uint32_t* sampleRate)
{
    fseek(f, 22, SEEK_SET);
    fread(nChannels, 2, 1, f);
    fread(sampleRate, 4, 1, f);
    fseek(f, 44, SEEK_SET);
    return 0;
}

SimpleChannel* playSound(const char* path, int loops) {
    printf("Playin sound %s\n", path);
    for (size_t ci = 0; ci < NUM_CHANNELS; ci++)
    {
        volatile SimpleChannel *channel = &channels[ci];
        if(channel->format != FORMAT_FREE) continue;

        FILE* f = fopen(path, "rb");
        if (!f) return nullptr;
        channel->data_pointer = f;
        uint16_t nChannels;
        uint32_t sampleRate;
        loadWaveFile(f, &nChannels, &sampleRate);
        // switch over to WAVE file format soon....
        ndspChnReset(ci);
        ndspChnSetInterp(ci, NDSP_INTERP_POLYPHASE);
        if (nChannels == 2)
        {
            ndspChnSetFormat(channel->channel_id, NDSP_FORMAT_STEREO_PCM16);
            channel->stereo=true;
        }
        else
        {
            ndspChnSetFormat(channel->channel_id, NDSP_FORMAT_MONO_PCM16);
            channel->stereo=false;
        }
        ndspChnSetRate(channel->channel_id, sampleRate);
        channel->format = FORMAT_PCM_FILE;
        channel->loops = loops;
        LightEvent_Signal(&sound_event);
        return (SimpleChannel *)channel;
    }
    return nullptr;
}

SimpleChannel* playSoundOGG(const char* path, int loops) {
    printf("Playin music %s\n", path);
    for (size_t ci = 0; ci < NUM_CHANNELS; ci++)
    {
        volatile SimpleChannel *channel = &channels[ci];
        if(channel->format != FORMAT_FREE) continue;

        FILE* f = fopen(path, "rb");
        if (!f) return nullptr;
        OggVorbis_File *vf = (OggVorbis_File*)malloc(sizeof(OggVorbis_File));
        if(!vf) {
            fclose(f);
            return nullptr;
        }
        if(ov_open(f,vf,nullptr,0))
        {
            free(vf);
            fclose(f);
            return nullptr;
        }
        ndspChnReset(ci);
        ndspChnSetInterp(ci, NDSP_INTERP_POLYPHASE);
        vorbis_info *vi = ov_info(vf,-1);
        if (vi->channels == 2)
        {
            ndspChnSetFormat(channel->channel_id, NDSP_FORMAT_STEREO_PCM16);
            channel->stereo=true;
        }
        else if (vi->channels == 1)
        {
            ndspChnSetFormat(channel->channel_id, NDSP_FORMAT_MONO_PCM16);
            channel->stereo=false;
        }
        else
        {
            ov_clear(vf);
            free(vf);
            return nullptr;
        }
        printf("Malloc'ed an oggmusic object at %p..\n", vf);
        ndspChnSetRate(channel->channel_id, vi->rate);
        channel->data_pointer = (void*)vf;
        channel->format = FORMAT_OGG_FILE;
        channel->loops = loops;
        LightEvent_Signal(&sound_event);
        return (SimpleChannel *)channel;
    }
    return nullptr;
}

bool audioInit() {
    LightEvent_Init(&sound_event, RESET_ONESHOT);
    ndspInit();

    ndspSetOutputMode(NDSP_OUTPUT_STEREO);

    // Allocate audio buffer
    const size_t bufferSize = BUFFER_SIZE * NUM_CHANNELS * NUM_BUFFERS;
    audio_buffer = (char *)linearAlloc(bufferSize);
    if(!audio_buffer) {
        printf("Failed to allocate audio buffer\n");
        return false;
    }

    // initialize channels and wavebufs
    for (size_t ci = 0; ci < NUM_CHANNELS; ci++)
    {
        channels[ci].channel_id = ci;
        channels[ci].format = FORMAT_FREE;
        channels[ci].data_pointer = NULL;

        ndspChnReset(ci);
        ndspChnSetInterp(ci, NDSP_INTERP_POLYPHASE);

        memset((void*) &channels[ci].wavebufs, 0, sizeof(channels[ci].wavebufs));
        for (size_t wi = 0; wi < NUM_BUFFERS; wi++)
        {
            channels[ci].wavebufs[wi].data_vaddr = audio_buffer + BUFFER_SIZE * (ci * NUM_BUFFERS + wi);
            channels[ci].wavebufs[wi].status = NDSP_WBUF_DONE;
        }
    }

    // begin setting up threading structure...
    ndspSetCallback(myAudioCallback, NULL);

    // Thanks to @mkst from sm64 3ds port
    int cpu = 0; // application core
    if (R_SUCCEEDED(APT_SetAppCpuTimeLimit(30)))
        cpu = 1; // system core

    // Set the thread priority to the main thread's priority ...
    int32_t priority = 0x30;
    svcGetThreadPriority(&priority, CUR_THREAD_HANDLE);
    // ... then subtract 1, as lower number => higher actual priority ...
    priority -= 1;
    // ... finally, clamp it between 0x18 and 0x3F to guarantee that it's valid.
    priority = priority < 0x18 ? 0x18 : priority;
    priority = priority > 0x3F ? 0x3F : priority;

    sound_thread = threadCreate(audioThread, NULL,
                                 THREAD_STACK_SZ, priority,
                                 cpu, false);

    if (sound_thread)
        printf("Created audio thread at %p on %s core\n", sound_thread, cpu ? "os" : "application");
    else
        printf("Failed to create audio thread\n");

    return (bool)sound_thread;
}

// Audio de-initialisation code
// Stops playback and frees the primary audio buffer
void audioExit() {
    sound_quit = true;
    LightEvent_Signal(&sound_event);

    // Free the audio thread
    threadJoin(sound_thread, UINT64_MAX);
    threadFree(sound_thread);

    for (size_t ci = 0; ci < NUM_CHANNELS; ci++)
    {
        closeChannel(&channels[ci]);
        ndspChnReset(channels[ci].channel_id);
    }

    linearFree(audio_buffer);

    ndspExit();
}

void audioPause() {
    for (size_t ci = 0; ci < NUM_CHANNELS; ci++)
    {
        ndspChnSetPaused(ci, true);
    }
}

void audioResume() {
    for (size_t ci = 0; ci < NUM_CHANNELS; ci++)
    {
        ndspChnSetPaused(ci, false);
    }
}

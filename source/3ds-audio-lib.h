#include <3ds.h>

#ifndef NUM_CHANNELS
#define NUM_CHANNELS 20
#define NUM_BUFFERS 3
#define BUFFER_SIZE (256 * (44100 / 1000))

#define THREAD_STACK_SZ 32 * 1024

#endif

typedef enum _CHANNEL_FORMAT {
 FORMAT_FREE,
 FORMAT_PCM_FILE,
 FORMAT_OGG_FILE,
 FORMAT_PCM_MEM,
} CHANNEL_FORMAT;

typedef struct _SimpleChannel {
    int channel_id;
    CHANNEL_FORMAT format;
    void *data_pointer;
    size_t data_left;
    ndspWaveBuf wavebufs[NUM_BUFFERS];
    bool kill;
    bool stereo;
    int loops;
    uint32_t id;
} SimpleChannel;

bool audioInit();

// Audio de-initialisation code
// Stops playback and frees the primary audio buffer
void audioExit();

void audioPause();
void audioResume();

SimpleChannel* playSound(const char* path, int loops=0);

SimpleChannel* playSoundOGG(const char* path, int loops=-1);

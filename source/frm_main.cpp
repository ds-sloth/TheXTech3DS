/*
 * TheXTech - A platform game engine ported from old source code for VB6
 *
 * Copyright (c) 2009-2011 Andrew Spinks, original VB6 code
 * Copyright (c) 2020-2020 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "globals.h"
#include "game_main.h"
#include "graphics.h"
#include "joystick.h"
#include "sound.h"
#include "editor.h"
#include "n3ds-clock.h"
#include "second_screen.h"

#include <AppPath/app_path.h>
// #include <Logger/logger.h>
#include <Utils/files.h>
#include <Utils/elapsed_timer.h>
#include <DirManager/dirman.h>
#include <chrono>
#include <fmt_format_ne.h>
#include "editor_screen.h"

#include <3ds.h>

#include "frm_main.h"

FrmMain::FrmMain()
{
    ScaleWidth = ScreenW;
    ScaleHeight = ScreenH;
}

uint8_t FrmMain::getKeyState(int key)
{
    // if(m_keyboardState)
    //     return m_keyboardState[key];
    return 0;
}

bool FrmMain::initSDL(const CmdLineSetup_t &setup)
{
    // 3ds libs
    aptInit();
    InitClockSpeed();
    gfxInitDefault();
    gfxSet3D(true); // Enable stereoscopic 3D
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    // consoleInit(GFX_BOTTOM, NULL);

    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    right = C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT);
    bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    // bottom = right;
    debugMode = false;

    for (int i = 0; i < 4; i++)
    {
        C3D_TexInitVRAM(&layer_texs[i], 512, 256, GPU_RGBA8);
        layer_targets[i] = C3D_RenderTargetCreateFromTex(&layer_texs[i], GPU_TEXFACE_2D, 0, GPU_RB_DEPTH24_STENCIL8);
        layer_subtexs[i] = {420, 240, 0., 1., 420./512., 1-(240./256.)};
        layer_ims[i].tex = &layer_texs[i];
        layer_ims[i].subtex = &layer_subtexs[i];
    }

    bool res = false;

    // LoadLogSettings(setup.interprocess, setup.verboseLogging);
    //Write into log the application start event
    // printf("<Application started>\n");

    updateViewport();

    repaint();
    doEvents();

    return res;
}

void FrmMain::freeSDL()
{
    GFX.unLoad();
    clearAllTextures();

    for (int i = 0; i < 4; i++)
    {
        C3D_TexDelete(&layer_texs[i]);
    }
    // 3ds libs
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    aptExit();

    // printf("<Application closed>");
    // CloseLog();
}

void FrmMain::show()
{
}

void FrmMain::hide()
{
}

void FrmMain::doEvents()
{
    hidScanInput();

    keys_held = hidKeysHeld();
    keys_pressed = hidKeysDown();
    keys_released = hidKeysUp();

    depthSlider = osGet3DSliderState();
    if (depthSlider > 0.05) numEyes = 2;
    else numEyes = 1;
    if (!aptMainLoop()) KillIt(); // could add panic save of some sort here...

    if (!LevelEditor)
        return;

    touchPosition touch;
    hidTouchRead(&touch);

    if (!editorScreen.active)
    {
        if ((keys_pressed & KEY_TOUCH) && (touch.py > 20))
        {
            int distance2 = (m_lastMousePosition.px - touch.px)*(m_lastMousePosition.px - touch.px)
                + (m_lastMousePosition.py - touch.py)*(m_lastMousePosition.py - touch.py);

            if (distance2 < 64)
                EditorControls.Mouse1 = true;
        }
        if (keys_released & KEY_TOUCH)
        {
            EditorControls.Mouse1 = false;
            MenuMouseRelease = true;
        }
        if (keys_held & KEY_TOUCH)
        {
            // not selector bar
            if (touch.py > 20)
            {
                MenuMouseX = -50;
                MenuMouseY = -50;
                EditorCursor.X = 100 + touch.px * 2;
                EditorCursor.Y = touch.py * 2;
                m_lastMousePosition = touch;
            }
            // selector bar
            else
            {
                MenuMouseDown = keys_held & KEY_TOUCH;
                MenuMouseX = 100 + touch.px * 2;
                MenuMouseY = touch.py * 2;
                m_lastMousePosition = {0, 0};
            }
        }
        MouseMove(EditorCursor.X, EditorCursor.Y, true);
    }
    else
    {
        MenuMouseRelease = keys_released & KEY_TOUCH;
        MenuMouseDown = keys_held & KEY_TOUCH;
        if (MenuMouseDown)
        {
            MenuMouseX = touch.px * 2;
            MenuMouseY = touch.py * 2;
        }
    }
}

void FrmMain::processEvent()
{
    return;
}

void FrmMain::waitEvents()
{
    doEvents();
}

bool FrmMain::isWindowActive()
{
    return true;
}

bool FrmMain::hasWindowMouseFocus()
{
    return true;
}

void FrmMain::eventResize()
{
    updateViewport();
    SetupScreens();
}

int FrmMain::setFullScreen(bool fs)
{
    return 0;
}

bool FrmMain::isSdlError()
{
    return false;
}

void FrmMain::initDraw(int screen)
{
    // enter the draw context!
    // FILE* log = fopen("/initdraw.txt", "wb");
    // fputs("open\n", log); fflush(log);
    // fprintf(log, "stack: %p\n", &log); fflush(log);
    if (screen == 0)
    {
        // fputs("hello\n", log); fflush(log);
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        // fputs("hello2\n", log); fflush(log);
        for (int layer = 0; layer < 4; layer++)
        {
            // fputs("hello3\n", log); fflush(log);
            C2D_TargetClear(layer_targets[layer], C2D_Color32f(0.0f, 0.0f, 0.0f, 0.0f));
        }
        // fputs("hello4\n", log); fflush(log);
        C2D_SceneBegin(layer_targets[2]); // screen plane target
    }
    else if (LevelEditor && !editorScreen.active)
    {
        setViewport(80, 0, 640, 480);
        // fputs("morp\n", log); fflush(log);
        C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
        // fputs("merp\n", log); fflush(log);
        C2D_SceneBegin(top);
    }
    else
    {
        // fputs("meep\n", log); fflush(log);
        C2D_TargetClear(bottom, C2D_Color32f(0.0f, 0.0f, 1.0f, 1.0f));
        // fputs("morp\n", log); fflush(log);
        C2D_SceneBegin(bottom);
    }
    // fputs("goodbue\n", log); fclose(log);
}

void FrmMain::setLayer(int layer)
{
    C2D_SceneBegin(layer_targets[layer]);
}

void FrmMain::finalizeDraw()
{
    resetViewport();
    // leave the draw context and wait for vblank...
    if (LevelEditor && !editorScreen.active)
    {
        C2D_TargetClear(bottom, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
        C2D_SceneBegin(bottom);
        // can be a bigger offset than this...
        C2D_DrawImageAt(layer_ims[0], -50, 0, 0);
        C2D_DrawImageAt(layer_ims[1], -50, 0, 0);
        C2D_DrawImageAt(layer_ims[2], -50, 0, 0);
        C2D_DrawImageAt(layer_ims[3], -50, 0, 0);
    }
    else if (numEyes == 1)
    {
        C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
        C2D_SceneBegin(top);
        C2D_DrawImageAt(layer_ims[0], -10, 0, 0);
        C2D_DrawImageAt(layer_ims[1], -10, 0, 0);
        C2D_DrawImageAt(layer_ims[2], -10, 0, 0);
        C2D_DrawImageAt(layer_ims[3], -10, 0, 0);
    }
    else
    {
        C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
        C2D_SceneBegin(top);
        C2D_DrawImageAt(layer_ims[0], -10 - (int)(10. * depthSlider), 0, 0);
        C2D_DrawImageAt(layer_ims[1], -10 - (int)(4. * depthSlider), 0, 0);
        C2D_DrawImageAt(layer_ims[2], -10, 0, 0);
        C2D_DrawImageAt(layer_ims[3], -10 + (int)(4. * depthSlider), 0, 0);

        C2D_TargetClear(right, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
        C2D_SceneBegin(right);
        C2D_DrawImageAt(layer_ims[0], -10 + (int)(10. * depthSlider), 0, 0);
        C2D_DrawImageAt(layer_ims[1], -10 + (int)(4. * depthSlider), 0, 0);
        C2D_DrawImageAt(layer_ims[2], -10, 0, 0);
        C2D_DrawImageAt(layer_ims[3], -10 - (int)(4. * depthSlider), 0, 0);
    }
    currentFrame ++;
    C3D_FrameEnd(0);
}

void FrmMain::repaint()
{
}

void FrmMain::updateViewport()
{
    resetViewport();
    offsetViewport(0, 0);
}

void FrmMain::resetViewport()
{
    setViewport(0, 0, ScreenW, ScreenH);
}

void FrmMain::setViewport(int x, int y, int w, int h)
{
    int offset_x = viewport_offset_x - viewport_x;
    int offset_y = viewport_offset_y - viewport_y;
    viewport_x = x/2;
    viewport_y = y/2;
    viewport_w = w/2;
    viewport_h = h/2;
    viewport_offset_x = viewport_x + offset_x;
    viewport_offset_y = viewport_y + offset_y;
}

void FrmMain::offsetViewport(int x, int y)
{
    viewport_offset_x = viewport_x+x;
    viewport_offset_y = viewport_y+y;
}

StdPicture FrmMain::LoadPicture(std::string path)
{
    StdPicture target;
    C2D_SpriteSheet sourceImage;
    if(!GameIsActive)
        return target; // do nothing when game is closed

    target.inited = false;
    target.path = path;
    if(target.path.empty())
        return target;

    target.inited = true;
    target.lazyLoaded = false;

    sourceImage = C2D_SpriteSheetLoad(target.path.c_str());
    loadTexture(target, sourceImage);

    num_textures_loaded ++;

    if(!target.texture)
        printf("FAILED TO LOAD!!! %s\n", path.c_str());
    return target;
}


StdPicture FrmMain::lazyLoadPicture(std::string path)
{
    StdPicture target;
    if(!GameIsActive)
        return target; // do nothing when game is closed

    target.inited = false;
    target.path = path;
    if(target.path.empty())
        return target;

    target.inited = true;

    target.lazyLoaded = true;

    // We need to figure out the height and width!
    std::string sizePath = path + ".size";
    FILE *fs;
    fs = fopen(sizePath.c_str(), "r");
    // NOT null-terminated: wwww\nhhhh\n
    char contents[10];
    if (fs != nullptr) {
        fread(&contents[0], 1, 10, fs);
        contents[4] = '\0';
        contents[9] = '\0';
        target.w = atoi(&contents[0]);
        target.h = atoi(&contents[5]);
        if (fclose(fs)) printf("lazyLoadPicture: Couldn't close file.\n");
    }
    // lazy load and unload to read dimensions if it doesn't exist.
    // unload is essential because lazy load would save the address incorrectly.
    else {
        lazyLoad(target);
        lazyUnLoad(target);
        printf("lazyLoadPicture: Couldn't open size file.\n");
    }

    return target;
}

void FrmMain::loadTexture(StdPicture &target, C2D_SpriteSheet &sheet)
{
    C2D_Image im = C2D_SpriteSheetGetImage(sheet, 0);

    target.texture = sheet;
    target.image = im;
    if (!target.w)
    {
        target.w = im.subtex->width*2;
        target.h = im.subtex->height*2;
    }

    m_textureBank.insert(sheet);
}

void FrmMain::loadTexture2(StdPicture &target, C2D_SpriteSheet &sheet)
{
    C2D_Image im = C2D_SpriteSheetGetImage(sheet, 0);

    target.texture2 = sheet;
    target.image2 = im;

    m_textureBank.insert(sheet);
}

void FrmMain::loadTexture3(StdPicture &target, C2D_SpriteSheet &sheet)
{
    C2D_Image im = C2D_SpriteSheetGetImage(sheet, 0);

    target.texture3 = sheet;
    target.image3 = im;

    m_textureBank.insert(sheet);
}

void FrmMain::lazyLoad(StdPicture &target)
{
    if(!target.inited || !target.lazyLoaded || target.texture)
        return;

    C2D_SpriteSheet sourceImage;
    std::string suppPath;

    sourceImage = C2D_SpriteSheetLoad(target.path.c_str()); // some other source image

    int i;

    if (!sourceImage) {
        // wish I knew the largest contiguous portion of memory
        // max tex should be 4194304
        for (i = 0; i < 10; i ++)
        {
            if (linearSpaceFree() > 4000000) break;
            if (!freeTextureMem()) break;
        }
        sourceImage = C2D_SpriteSheetLoad(target.path.c_str());

        if (!sourceImage) {
            for (i = 0; i < 10; i ++)
            {
                if (linearSpaceFree() > 8000000) break;
                if (!freeTextureMem()) break;
            }
            sourceImage = C2D_SpriteSheetLoad(target.path.c_str());

            if (!sourceImage) {
                for (i = 0; i < 25; i ++)
                {
                    if (linearSpaceFree() > 20000000) break;
                    if (!freeTextureMem()) break;
                }
                sourceImage = C2D_SpriteSheetLoad(target.path.c_str());

                if (!sourceImage) {
                    printf("Permanently failed to load %s, %lu free\n", target.path.c_str(), linearSpaceFree());
                    printf("Error: %d (%s)\n", errno, strerror(errno));
                    target.inited = false;
                    return;
                }
            }
        }
    }

    loadTexture(target, sourceImage);

    if (target.h > 2048) {
        suppPath = target.path + '1';
        sourceImage = C2D_SpriteSheetLoad(suppPath.c_str());
        if (!sourceImage) {
            for (i = 0; i < 10; i ++)
            {
                if (linearSpaceFree() > 16000000) break;
                if (!freeTextureMem()) break;
            }
            sourceImage = C2D_SpriteSheetLoad(suppPath.c_str());
        }
        if (sourceImage) loadTexture2(target, sourceImage);
    }
    if (target.h > 4096) {
        suppPath = target.path + '2';
        sourceImage = C2D_SpriteSheetLoad(suppPath.c_str());
        if (!sourceImage) {
            for (i = 0; i < 10; i ++)
            {
                if (linearSpaceFree() > 16000000) break;
                if (!freeTextureMem()) break;
            }
            sourceImage = C2D_SpriteSheetLoad(suppPath.c_str());
        }
        if (sourceImage) loadTexture3(target, sourceImage);
    }

    num_textures_loaded ++;

    if (target.w >= 256 || target.h >= 256)
    {
        m_bigPictures.insert(&target);
        num_big_textures_loaded ++;
    }

    if (linearSpaceFree() < 4194304) freeTextureMem();
}

bool FrmMain::freeTextureMem() // make it take an amount of memory, someday.....
{
    printf("Freeing texture memory...\n");
    StdPicture* oldest = nullptr;
    uint32_t earliestDraw = 0;
    StdPicture* second_oldest = nullptr;
    uint32_t second_earliestDraw = 0;
    for (StdPicture* poss : m_bigPictures)
    {
        if (poss->texture && poss->lazyLoaded && (poss->lastDrawFrame+30 < currentFrame))
        {
            if ((oldest == nullptr) || (poss->lastDrawFrame < earliestDraw))
            {
                second_oldest = oldest;
                second_earliestDraw = earliestDraw;
                oldest = poss;
                earliestDraw = poss->lastDrawFrame;
            }
            else if ((second_oldest == nullptr) || (poss->lastDrawFrame < second_earliestDraw))
            {
                second_oldest = poss;
                second_earliestDraw = poss->lastDrawFrame;
            }
        }
    }
    if (oldest == nullptr) return false;
    printf("Clearing %p, %p\n", oldest, second_oldest);
    printf("Clearing %s, %s\n", oldest->path.c_str(), (second_oldest) ? second_oldest->path.c_str() : "");
    lazyUnLoad(*oldest);
    if (second_oldest) lazyUnLoad(*second_oldest);
    return true;
}

void FrmMain::lazyUnLoad(StdPicture &target)
{
    if(!target.inited || !target.lazyLoaded || !target.texture)
        return;
    deleteTexture(target, true);
}


SDL_Point FrmMain::MapToScr(int x, int y)
{
    return {
        static_cast<int>((static_cast<float>(x) - offset_x) / viewport_scale_x),
        static_cast<int>((static_cast<float>(y) - offset_y) / viewport_scale_y)
    };
}

void FrmMain::deleteTexture(StdPicture &tx, bool lazyUnload)
{
    // printf("Clearing %s from %lu", tx.path.c_str(), linearSpaceFree());
    if(!tx.inited)
        return;

    if(m_bigPictures.find(&tx) != m_bigPictures.end())
    {
        m_bigPictures.erase(&tx);
        num_big_textures_loaded --;
    }

    if(tx.texture)
    {
        num_textures_loaded --;
        if(m_textureBank.find(tx.texture) != m_textureBank.end())
            m_textureBank.erase(tx.texture);
        C2D_SpriteSheetFree(tx.texture);
        tx.texture = nullptr;
    }

    if(tx.texture2)
    {
        if(m_textureBank.find(tx.texture2) != m_textureBank.end())
            m_textureBank.erase(tx.texture2);
        C2D_SpriteSheetFree(tx.texture2);
        tx.texture2 = nullptr;
    }

    if(tx.texture3)
    {
        if(m_textureBank.find(tx.texture3) != m_textureBank.end())
            m_textureBank.erase(tx.texture3);
        C2D_SpriteSheetFree(tx.texture3);
        tx.texture3 = nullptr;
    }

    if(!lazyUnload)
    {
        tx.inited = false;
        tx.lazyLoaded = false;
        tx.w = 0;
        tx.h = 0;
        tx.frame_w = 0;
        tx.frame_h = 0;
    }
    // printf(" to %lu\n", linearSpaceFree());
}

void FrmMain::clearAllTextures()
{
    for(C2D_SpriteSheet tx : m_textureBank)
        C2D_SpriteSheetFree(tx);
    m_textureBank.clear();
}

void FrmMain::clearBuffer()
{
    // printf("Clearing that buffer...\n");
    C3D_FrameBegin(0);
    C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
    C2D_SceneBegin(top);
    renderRect(0,0,ScreenW,ScreenH,0.f,0.f,0.f,1.f,true);
    C2D_TargetClear(right, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
    C2D_SceneBegin(right);
    renderRect(0,0,ScreenW,ScreenH,0.f,0.f,0.f,1.f,true);
    C2D_TargetClear(bottom, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
    C2D_SceneBegin(bottom);
    renderRect(0,0,ScreenW,ScreenH,0.f,0.f,0.f,1.f,true);
    C3D_FrameEnd(0);
}

void FrmMain::toggleDebug()
{
    // printf("Clearing that buffer...\n");
    if (debugMode)
    {
        C3D_FrameBegin(0);
        C2D_TargetClear(bottom, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
        C2D_SceneBegin(bottom);
        renderRect(0,0,ScreenW,ScreenH,0.f,0.f,0.f,1.f,true);
        C3D_FrameEnd(0);
    }
    debugMode = !debugMode;
}

void FrmMain::renderRect(int x, int y, int w, int h, float red, float green, float blue, float alpha, bool filled)
{
    uint32_t clr = C2D_Color32f(red, green, blue, alpha);

    // Filled is always True in this game
    if (filled)
        C2D_DrawRectSolid(x/2+viewport_offset_x,
                          y/2+viewport_offset_y,
                          0, w/2, h/2, clr);
    else
    {
        C2D_DrawRectangle(x/2+viewport_offset_x,
                          y/2+viewport_offset_y,
                          0, 1, h/2, clr, clr, clr, clr);
        C2D_DrawRectangle(x/2+viewport_offset_x+w/2-1,
                          y/2+viewport_offset_y,
                          0, 1, h/2, clr, clr, clr, clr);
        C2D_DrawRectangle(x/2+viewport_offset_x,
                          y/2+viewport_offset_y,
                          0, w/2, 1, clr, clr, clr, clr);
        C2D_DrawRectangle(x/2+viewport_offset_x,
                          y/2+viewport_offset_y+h/2-1,
                          0, w/2, 1, clr, clr, clr, clr);
    }
}

void FrmMain::renderRectBR(int _left, int _top, int _right, int _bottom, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    renderRect(_left, _top, _right-_left, _bottom-_top, red, green, blue, alpha, true);
}

void FrmMain::renderCircle(int cx, int cy, int radius, float red, float green, float blue, float alpha, bool filled)
{
    // this is never used
}

inline int ROUNDDIV2(int x)
{
    return (x<0)?(x-1)/2:x/2;
}

inline float ROUNDDIV2(float x)
{
    return std::nearbyintf(std::roundf(x)/2.f);
}

inline float ROUNDDIV2(double x)
{
    return std::nearbyintf(std::roundf((float)x)/2.f);
}

inline float FLOORDIV2(float x)
{
    return std::floor(x/2.f);
}

#include "custom_draw_supplement.h"

void FrmMain::renderTexturePrivate(float xDst, float yDst, float wDst, float hDst,
                             StdPicture &tx,
                             float xSrc, float ySrc,
                             bool shadow)
{
    if(!tx.inited)
        return;

    if(!tx.texture && tx.lazyLoaded)
        lazyLoad(tx);

    tx.lastDrawFrame = currentFrame;

    if(!tx.texture)
        return;
    if(xDst > viewport_w || yDst > viewport_h)
        return;

    // texture boundaries
    // this never happens unless there was an invalid input
    // if((xSrc < 0.f) || (ySrc < 0.f)) return;

    if(xDst < 0.f)
    {
        xSrc -= xDst;
        wDst += xDst;
        xDst = 0.f;
        if (wDst > viewport_w)
            wDst = viewport_w;
    }
    else if(xDst + wDst > viewport_w)
    {
        wDst = (viewport_w - xDst);
    }
    if(yDst < 0.f)
    {
        ySrc -= yDst;
        hDst += yDst;
        yDst = 0.f;
        if (hDst > viewport_h)
            hDst = viewport_h;
    }
    else if(yDst + hDst > viewport_h)
    {
        hDst = (viewport_h - yDst);
    }

    C2D_Image* to_draw = nullptr;
    C2D_Image* to_draw_2 = nullptr;

    // Don't go more than size of texture
    // Failure conditions should only happen if texture is smaller than expected
    if(xSrc + wDst > tx.w/2)
    {
        wDst = tx.w/2 - xSrc;
        if(wDst < 0.f)
            return;
    }
    if(ySrc + hDst > tx.h/2)
    {
        hDst = tx.h/2 - ySrc;
        if(hDst < 0.f)
            return;
    }

    if(ySrc + hDst > 1024.f)
    {
        if(ySrc + hDst > 2048.f)
        {
            if(tx.texture3)
                to_draw = &tx.image3;
            if(ySrc < 2048.f && tx.texture2)
                to_draw_2 = &tx.image2;
            ySrc -= 1024.f;
        }
        else
        {
            if(tx.texture2)
                to_draw = &tx.image2;
            if(ySrc < 1024.f)
                to_draw_2 = &tx.image;
        }
        // draw the top pic
        if(to_draw_2 != nullptr)
        {
            C2D_DrawImage_Custom(*to_draw_2, xDst+viewport_offset_x, yDst+viewport_offset_y,
                                 xSrc, ySrc, wDst, 1024.f-ySrc, shadow);
            yDst += (1024.f - ySrc);
            hDst -= (1024.f - ySrc);
            ySrc = 0.f;
        }
        else
            ySrc -= 1024.f;
    }
    else to_draw = &tx.image;

    if (to_draw == nullptr) return;

    C2D_DrawImage_Custom(*to_draw, xDst+viewport_offset_x, yDst+viewport_offset_y,
                         xSrc, ySrc, wDst, hDst, shadow);
}

void FrmMain::renderTextureScale(float xDst, float yDst, float wDst, float hDst,
                             StdPicture &tx,
                             float xSrc, float ySrc, float wSrc, float hSrc,
                             bool shadow)
{
    xDst = ROUNDDIV2(xDst);
    yDst = ROUNDDIV2(yDst);
    wDst = ROUNDDIV2(wDst);
    hDst = ROUNDDIV2(hDst),
    xSrc = xSrc/2;
    ySrc = ySrc/2;
    wSrc = wSrc/2;
    hSrc = hSrc/2;
    // identical to renderTexturePrivate apart from last line.
    if(!tx.inited)
        return;

    if(!tx.texture && tx.lazyLoaded)
        lazyLoad(tx);

    tx.lastDrawFrame = currentFrame;

    if(!tx.texture)
        return;
    if(xDst > viewport_w || yDst > viewport_h)
        return;

    // texture boundaries
    // this never happens unless there was an invalid input
    // if((xSrc < 0.f) || (ySrc < 0.f)) return;

    if(xDst < 0.f)
    {
        xSrc -= xDst;
        wDst += xDst;
        xDst = 0.f;
        if (wDst > viewport_w)
            wDst = viewport_w;
    }
    else if(xDst + wDst > viewport_w)
    {
        wDst = (viewport_w - xDst);
    }
    if(yDst < 0.f)
    {
        ySrc -= yDst;
        hDst += yDst;
        yDst = 0.f;
        if (hDst > viewport_h)
            hDst = viewport_h;
    }
    else if(yDst + hDst > viewport_h)
    {
        hDst = (viewport_h - yDst);
    }

    C2D_Image* to_draw = nullptr;
    C2D_Image* to_draw_2 = nullptr;

    // Don't go more than size of texture
    // Failure conditions should only happen if texture is smaller than expected
    if(xSrc + wDst > tx.w/2)
    {
        wDst = tx.w/2 - xSrc;
        if(wDst < 0.f)
            return;
    }
    if(ySrc + hDst > tx.h/2)
    {
        hDst = tx.h/2 - ySrc;
        if(hDst < 0.f)
            return;
    }

    if(ySrc + hDst > 1024.f)
    {
        if(ySrc + hDst > 2048.f)
        {
            if(tx.texture3)
                to_draw = &tx.image3;
            if(ySrc < 2048.f && tx.texture2)
                to_draw_2 = &tx.image2;
            ySrc -= 1024.f;
        }
        else
        {
            if(tx.texture2)
                to_draw = &tx.image2;
            if(ySrc < 1024.f)
                to_draw_2 = &tx.image;
        }
        // draw the top pic
        if(to_draw_2 != nullptr)
        {
            C2D_DrawImage_Custom(*to_draw_2, xDst+viewport_offset_x, yDst+viewport_offset_y,
                                 xSrc, ySrc, wDst, 1024.f-ySrc, shadow);
            yDst += (1024.f - ySrc);
            hDst -= (1024.f - ySrc);
            ySrc = 0.f;
        }
        else
            ySrc -= 1024.f;
    }
    else to_draw = &tx.image;

    if (to_draw == nullptr) return;

    C2D_DrawImage_Custom(*to_draw, xDst+viewport_offset_x, yDst+viewport_offset_y, wDst, hDst,
                         xSrc, ySrc, wSrc, hSrc, shadow);
}

void FrmMain::renderTexture(double xDst, double yDst, double wDst, double hDst,
                            StdPicture &tx,
                            unsigned int xSrc, unsigned int ySrc,
                            bool shadow)
{
    renderTexturePrivate(ROUNDDIV2(xDst),
                   ROUNDDIV2(yDst),
                   ROUNDDIV2(wDst),
                   ROUNDDIV2(hDst),
                   tx,
                   xSrc/2,
                   ySrc/2,
                   shadow);
}

void FrmMain::renderTexture(double xDst, double yDst, int wDst, int hDst,
                            StdPicture &tx,
                            unsigned int xSrc, unsigned int ySrc,
                            bool shadow)
{
    renderTexturePrivate(ROUNDDIV2(xDst),
                   ROUNDDIV2(yDst),
                   wDst/2,
                   hDst/2,
                   tx,
                   xSrc/2,
                   ySrc/2,
                   shadow);
}

void FrmMain::renderTexture(int xDst, int yDst, int wDst, int hDst,
                            StdPicture &tx,
                            unsigned int xSrc, unsigned int ySrc,
                            bool shadow)
{
    renderTexturePrivate(ROUNDDIV2(xDst),
                   ROUNDDIV2(yDst),
                   wDst/2,
                   hDst/2,
                   tx,
                   xSrc/2,
                   ySrc/2,
                   shadow);
}

void FrmMain::renderTexture(int xDst, int yDst, StdPicture &tx, bool shadow)
{
    renderTexturePrivate(ROUNDDIV2(xDst),
                   ROUNDDIV2(yDst),
                   tx.w/2,
                   tx.h/2,
                   tx,
                   0.f,
                   0.f,
                   shadow);
}

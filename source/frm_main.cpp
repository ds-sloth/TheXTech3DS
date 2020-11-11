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
#include "custom_draw_image.h"
#include "n3ds-clock.h"

#include <AppPath/app_path.h>
// #include <Logger/logger.h>
#include <Utils/files.h>
#include <Utils/elapsed_timer.h>
#include <DirManager/dirman.h>
#include <Utils/maths.h>
#include <chrono>
#include <fmt_format_ne.h>

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
    consoleInit(GFX_BOTTOM, NULL);

    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    right = C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT);

    bool res = false;

    // LoadLogSettings(setup.interprocess, setup.verboseLogging);
    //Write into log the application start event
    printf("<Application started>");

    updateViewport();

    repaint();
    doEvents();

    return res;
}

void FrmMain::freeSDL()
{
    GFX.unLoad();
    clearAllTextures();

    // 3ds libs
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    aptExit();

    printf("<Application closed>");
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
    depthSlider = osGet3DSliderState();
    if (depthSlider > 0.05) numEyes = 2;
    else numEyes = 1;
    if (!aptMainLoop()) KillIt(); // could add panic save of some sort here...
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

void FrmMain::initDraw(int eye)
{
    // enter the draw context!
    if (eye == 0) {
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
        C2D_SceneBegin(top);
        if (numEyes == 2) currentEye = 0;
        else currentEye = -1;
    }
    else {
        C2D_TargetClear(right, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
        C2D_SceneBegin(right);
        currentEye = 2;
    }
    setDefaultDepth(0);
}

void FrmMain::finalizeDraw()
{
    // leave the draw context and wait for vblank...
    currentFrame ++;
    C3D_FrameEnd(0);
}

void FrmMain::repaint()
{
    int w, h, off_x, off_y, wDst, hDst;
    float scale_x, scale_y;
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
    viewport_x = x;
    viewport_y = y;
    viewport_w = w;
    viewport_h = h;
    viewport_offset_x = viewport_x + offset_x;
    viewport_offset_y = viewport_y + offset_y;
}

void FrmMain::offsetViewport(int x, int y)
{
    viewport_offset_x = viewport_x+x-10;
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
                if (linearSpaceFree() > 10000000) break;
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
                if (linearSpaceFree() > 10000000) break;
                if (!freeTextureMem()) break;
            }
            sourceImage = C2D_SpriteSheetLoad(suppPath.c_str());
        }
        if (sourceImage) loadTexture3(target, sourceImage);
    }

    if (target.w >= 256 || target.h >= 256)
        m_bigPictures.insert(&target);

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
    printf("Clearing %s, %s\n", oldest->path.c_str(), second_oldest->path.c_str());
    printf("Clearing %p, %p\n", oldest, second_oldest);
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

    if(m_bigPictures.find(&tx) != m_bigPictures.end()) m_bigPictures.erase(&tx);

    if(tx.texture)
    {
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
    // SDL_SetRenderDrawColor(m_gRenderer, 0, 0, 0, 255);
    // SDL_RenderClear(m_gRenderer);
}

void FrmMain::setDefaultDepth(int depth) {
    defaultDepth = depth;
}
void FrmMain::renderRect(int x, int y, int w, int h, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, bool filled, int depth)
{
    if (depth == -10000) depth = defaultDepth;
    uint32_t clr = C2D_Color32(red, green, blue, alpha);

    // Filled is always True in this game
    if (currentEye == -1)
        C2D_DrawRectSolid((x+viewport_offset_x)/2,
                          (y+viewport_offset_y)/2,
                          0, w/2, h/2, clr);
    else if (currentEye == 0)
        C2D_DrawRectSolid((x+viewport_offset_x)/2 - (int)(depth * depthSlider),
                          (y+viewport_offset_y)/2,
                          0, w/2, h/2, clr);
    else
        C2D_DrawRectSolid((x+viewport_offset_x)/2 + (int)(depth * depthSlider),
                          (y+viewport_offset_y)/2,
                          0, w/2, h/2, clr);
}

void FrmMain::renderRectBR(int _left, int _top, int _right, int _bottom, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, int depth)
{
    if (depth == -10000) depth = defaultDepth;
    renderRect(_left, _top, _right-_left, _bottom-_top, red, green, blue, alpha, true, depth);
}

void FrmMain::renderCircle(int cx, int cy, int radius, float red, float green, float blue, float alpha, bool filled, int depth)
{
    // this is never used
}

void FrmMain::renderTextureI(int xDst, int yDst, int wDst, int hDst,
                             StdPicture &tx,
                             int xSrc, int ySrc,
                             double rotateAngle, SDL_Point *center, unsigned int flip,
                             bool shadow, int depth)
{
    if (depth == -10000) depth = defaultDepth;
    if(!tx.inited)
        return;

    if(!tx.texture && tx.lazyLoaded)
        lazyLoad(tx);

    tx.lastDrawFrame = currentFrame;

    if(!tx.texture)
        return;

    if(xDst < 0)
    {
        xSrc -= xDst;
        wDst += xDst;
        xDst = 0;
    }
    if(xDst + wDst > viewport_w)
    {
        if(xDst > viewport_w) return;
        wDst = (viewport_w - xDst);
    }
    if(yDst < 0)
    {
        ySrc -= yDst;
        hDst += yDst;
        yDst = 0;
    }
    if(yDst + hDst > viewport_h)
    {
        if(yDst > viewport_h) return;
        hDst = (viewport_h - yDst);
    }

    // texture boundaries
    if((xSrc < 0) || (ySrc < 0)) return;

    // Don't go more than size of texture
    if(xSrc + wDst > tx.w)
    {
        wDst = tx.w - xSrc;
        if(wDst < 0)
            wDst = 0;
    }
    if(ySrc + hDst > tx.h)
    {
        hDst = tx.h - ySrc;
        if(hDst < 0)
            hDst = 0;
    }

    C2D_Image* to_draw = nullptr;
    C2D_Image* to_draw_2 = nullptr;
    if(ySrc + hDst > 2048)
    {
        if(ySrc + hDst > 4096)
        {
            if(tx.texture3)
                to_draw = &tx.image3;
            if(ySrc < 4096 && tx.texture2)
                to_draw_2 = &tx.image2;
            ySrc -= 2048;
        }
        else
        {
            if(tx.texture2)
                to_draw = &tx.image2;
            if(ySrc < 2048)
                to_draw_2 = &tx.image;
        }
        // draw the top pic
        if(to_draw_2 != nullptr)
        {
            if (currentEye == -1)
                C2D_DrawImage_Custom(*to_draw_2, (xDst+viewport_offset_x)/2, (yDst+viewport_offset_y)/2, wDst/2, (2048-ySrc)/2,
                                     xSrc/2, ySrc/2, wDst/2, (2048-ySrc)/2, 0, flip, shadow);
            else if (currentEye == 0)
                C2D_DrawImage_Custom(*to_draw_2, (xDst+viewport_offset_x)/2 - (int)(depth * depthSlider), (yDst+viewport_offset_y)/2, wDst/2, (2048-ySrc)/2,
                                     xSrc/2, ySrc/2, wDst/2, (2048-ySrc)/2, 0, flip, shadow);
            else
                C2D_DrawImage_Custom(*to_draw_2, (xDst+viewport_offset_x)/2 + (int)(depth * depthSlider), (yDst+viewport_offset_y)/2, wDst/2, (2048-ySrc)/2,
                                     xSrc/2, ySrc/2, wDst/2, (2048-ySrc)/2, 0, flip, shadow);
            yDst += (2048 - ySrc);
            hDst -= (2048 - ySrc);
            ySrc = 0;
        }
        else
            ySrc -= 2048;
    }
    else to_draw = &tx.image;

    if (to_draw == nullptr) return;

    // add viewport positioning code...
    if (currentEye == -1)
        C2D_DrawImage_Custom(*to_draw, (xDst+viewport_offset_x)/2, (yDst+viewport_offset_y)/2, wDst/2, hDst/2,
                             xSrc/2, ySrc/2, wDst/2, hDst/2, 0, flip, shadow);
    else if (currentEye == 0)
        C2D_DrawImage_Custom(*to_draw, (xDst+viewport_offset_x)/2 - (int)(depth * depthSlider), (yDst+viewport_offset_y)/2, wDst/2, hDst/2,
                             xSrc/2, ySrc/2, wDst/2, hDst/2, 0, flip, shadow);
    else
        C2D_DrawImage_Custom(*to_draw, (xDst+viewport_offset_x)/2 + (int)(depth * depthSlider), (yDst+viewport_offset_y)/2, wDst/2, hDst/2,
                             xSrc/2, ySrc/2, wDst/2, hDst/2, 0, flip, shadow);
}

void FrmMain::renderTexture(double xDst, double yDst, double wDst, double hDst,
                            StdPicture &tx,
                            int xSrc, int ySrc,
                            bool shadow, int depth)
{
    const unsigned int flip = SDL_FLIP_NONE;
    renderTextureI((int)xDst,
                   (int)yDst,
                   (int)wDst,
                   (int)hDst,
                   tx,
                   xSrc,
                   ySrc,
                   0.0, nullptr, flip,
                   shadow, depth);
}

void FrmMain::renderTextureFL(double xDst, double yDst, double wDst, double hDst,
                              StdPicture &tx,
                              int xSrc, int ySrc,
                              double rotateAngle, SDL_Point *center, unsigned int flip,
                              bool shadow, int depth)
{
    renderTextureI((int)xDst,
                   (int)yDst,
                   (int)wDst,
                   (int)hDst,
                   tx,
                   xSrc,
                   ySrc,
                   rotateAngle, center, flip,
                   shadow, depth);
}

void FrmMain::renderTexture(int xDst, int yDst, StdPicture &tx, bool shadow, int depth)
{
    const unsigned int flip = SDL_FLIP_NONE;
    renderTextureI(xDst,
                   yDst,
                   tx.w,
                   tx.h,
                   tx,
                   0,
                   0,
                   0.0, nullptr, flip,
                   shadow, depth);
}

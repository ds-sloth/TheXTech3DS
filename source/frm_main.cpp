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
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    consoleInit(GFX_BOTTOM, NULL);

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
    while(false)
    {
        processEvent();
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

void FrmMain::repaint()
{
    int w, h, off_x, off_y, wDst, hDst;
    float scale_x, scale_y;
/*
    SDL_SetRenderTarget(m_gRenderer, nullptr);

    // Get the size of surface where to draw the scene
    SDL_GetRendererOutputSize(m_gRenderer, &w, &h);

    // Calculate the size difference factor
    scale_x = float(w) / ScaleWidth;
    scale_y = float(h) / ScaleHeight;

    wDst = w;
    hDst = h;

    // Keep aspect ratio
    if(scale_x > scale_y) // Width more than height
    {
        wDst = int(scale_y * ScaleWidth);
        hDst = int(scale_y * ScaleHeight);
    }
    else if(scale_x < scale_y) // Height more than width
    {
        hDst = int(scale_x * ScaleHeight);
        wDst = int(scale_x * ScaleWidth);
    }

    // Align the rendering scene to the center of screen
    off_x = (w - wDst) / 2;
    off_y = (h - hDst) / 2;

    SDL_SetRenderDrawColor(m_gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_gRenderer);

    SDL_Rect destRect = {off_x, off_y, wDst, hDst};
    SDL_Rect sourceRect = {0, 0, ScaleWidth, ScaleHeight};

    SDL_SetTextureColorMod(m_tBuffer, 255, 255, 255);
    SDL_SetTextureAlphaMod(m_tBuffer, 255);
    SDL_RenderCopyEx(m_gRenderer, m_tBuffer, &sourceRect, &destRect, 0.0, nullptr, SDL_FLIP_NONE);

    SDL_RenderPresent(m_gRenderer);
    SDL_SetRenderTarget(m_gRenderer, m_tBuffer);
*/
}

void FrmMain::updateViewport()
{
    /*
    float w, w1, h, h1;
    int   wi, hi;
    wi = ScreenW;
    hi = ScreenH;

    SDL_GetWindowSize(m_window, &wi, &hi);
    // ScaleWidth = wi;
    // ScaleHeight = hi;
    // if (ScaleWidth < 512) ScaleWidth = 512;
    // if (ScaleHeight < 384) ScaleHeight = 384;
    // if (ScaleWidth > 1280) ScaleWidth = 1280;
    // if (ScaleHeight > 720) ScaleHeight = 720;
    // Set_Screen(ScaleWidth, ScaleHeight);
    // SDL_DestroyTexture(m_tBuffer);
    // m_tBuffer = SDL_CreateTexture(m_gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, ScreenW, ScreenH);
    // SDL_SetRenderTarget(m_gRenderer, m_tBuffer);

    w = wi;
    h = hi;
    w1 = w;
    h1 = h;

    scale_x = w / ScaleWidth;
    scale_y = h / ScaleHeight;
    viewport_scale_x = scale_x;
    viewport_scale_y = scale_y;

    viewport_offset_x = 0;
    viewport_offset_y = 0;

    if(scale_x > scale_y)
    {
        w1 = scale_y * ScaleWidth;
        viewport_scale_x = w1 / ScaleWidth;
    }
    else if(scale_x < scale_y)
    {
        h1 = scale_x * ScaleHeight;
        viewport_scale_y = h1 / ScaleHeight;
    }

    offset_x = (w - w1) / 2;
    offset_y = (h - h1) / 2;

    viewport_x = 0;
    viewport_y = 0;
    viewport_w = static_cast<int>(w1);
    viewport_h = static_cast<int>(h1);
    */
}

void FrmMain::resetViewport()
{
    updateViewport();
    // SDL_RenderSetViewport(m_gRenderer, nullptr);
}

void FrmMain::setViewport(int x, int y, int w, int h)
{
    // SDL_Rect topLeftViewport = {x, y, w, h};
    // SDL_RenderSetViewport(m_gRenderer, &topLeftViewport);

    viewport_x = x;
    viewport_y = y;
    viewport_w = w;
    viewport_h = h;
}

void FrmMain::offsetViewport(int x, int y)
{
    if(viewport_offset_x != x || viewport_offset_y != y)
    {
        viewport_offset_x = x;
        viewport_offset_y = y;
    }
}

StdPicture FrmMain::LoadPicture(std::string path)
{
    StdPicture target;
    if(!GameIsActive)
        return target; // do nothing when game is closed
    target = lazyLoadPicture(path);
    lazyLoad(target);
    target.lazyLoaded = false;
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
    return target;
}

void FrmMain::loadTexture(StdPicture &target, C2D_SpriteSheet &sheet)
{
    C2D_Image im = C2D_SpriteSheetGetImage(sheet, 0);

    target.texture = sheet;
    target.image = im;
    target.w = im.subtex->width*2;
    target.h = im.subtex->height*2;

    m_textureBank.insert(sheet);
}


void FrmMain::lazyLoad(StdPicture &target)
{
    if(!target.inited || !target.lazyLoaded || target.texture)
        return;

    C2D_SpriteSheet sourceImage;

    sourceImage = C2D_SpriteSheetLoad(target.path.c_str()); // some other source image

    loadTexture(target, sourceImage);
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
    if(!tx.inited || !tx.texture)
    {
        if(!lazyUnload)
            tx.inited = false;
        return;
    }

    auto corpseIt = m_textureBank.find(tx.texture);
    if(corpseIt == m_textureBank.end())
    {
        if(tx.texture)
            C2D_SpriteSheetFree(tx.texture);
        tx.texture = nullptr;
        if(!lazyUnload)
            tx.inited = false;
        return;
    }

    C2D_SpriteSheet corpse = *corpseIt;
    if(corpse)
        C2D_SpriteSheetFree(corpse);
    m_textureBank.erase(corpse);

    tx.texture = nullptr;
    if(!lazyUnload)
        tx.inited = false;

    if(!lazyUnload)
    {
        tx.lazyLoaded = false;
        tx.w = 0;
        tx.h = 0;
        tx.frame_w = 0;
        tx.frame_h = 0;
    }
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
void FrmMain::renderRect(int x, int y, int w, int h, float red, float green, float blue, float alpha, bool filled, int depth)
{
    if (depth == -10000) depth = defaultDepth;
    uint32_t clr = ((uint32_t)(255.f * red) << 24) +
                 ((uint32_t)(255.f * green) << 16) +
                 ((uint32_t)(255.f * blue) << 8) +
                 ((uint32_t)(255.f * alpha));

    if (filled) {
        // do the offset thingy
        C2D_DrawRectSolid(x + viewport_offset_x,
                          y + viewport_offset_y,
                          depth,
                          w,
                          h,
                          clr);
    }
    else {
        // do nothing for now... :(
    }
}

void FrmMain::renderRectBR(int _left, int _top, int _right, int _bottom, float red, float green, float blue, float alpha, int depth)
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
                             float red, float green, float blue, float alpha, int depth)
{
    if (depth == -10000) depth = defaultDepth;
    if(!tx.inited)
        return;

    if(!tx.texture && tx.lazyLoaded)
        lazyLoad(tx);

    if(!tx.texture)
    {
        // D_printfNA("Attempt to render an empty texture!");
        printf("Attempt to render an empty texture!\n");
        return;
    }

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

    // SDL_Rect destRect = {xDst + viewport_offset_x, yDst + viewport_offset_y, wDst, hDst};
    // SDL_Rect sourceRect;
    // if(tx.w_orig == 0 && tx.h_orig == 0)
    //     sourceRect = {xSrc, ySrc, wDst, hDst};
    // else
    //     sourceRect = {int(tx.w_scale * xSrc), int(tx.h_scale * ySrc), int(tx.w_scale * wDst), int(tx.h_scale * hDst)};

    // SDL_SetTextureColorMod(tx.texture,
    //                        static_cast<unsigned char>(255.f * red),
    //                        static_cast<unsigned char>(255.f * green),
    //                        static_cast<unsigned char>(255.f * blue));
    // SDL_SetTextureAlphaMod(tx.texture, static_cast<unsigned char>(255.f * alpha));
    // SDL_RenderCopyEx(m_gRenderer, tx.texture, &sourceRect, &destRect,
    //                  rotateAngle, center, static_cast<SDL_RendererFlip>(flip));
    C2D_DrawImage_Custom(tx.image, xDst/2, yDst/2, wDst/2, hDst/2,
                         xSrc/2, ySrc/2, wDst/2, hDst/2, depth, flip, 0);
}

void FrmMain::renderTexture(double xDst, double yDst, double wDst, double hDst,
                            StdPicture &tx,
                            int xSrc, int ySrc,
                            float red, float green, float blue, float alpha, int depth)
{
    const unsigned int flip = SDL_FLIP_NONE;
    renderTextureI(Maths::iRound(xDst),
                   Maths::iRound(yDst),
                   Maths::iRound(wDst),
                   Maths::iRound(hDst),
                   tx,
                   xSrc,
                   ySrc,
                   0.0, nullptr, flip,
                   red, green, blue, alpha, depth);
}

void FrmMain::renderTextureFL(double xDst, double yDst, double wDst, double hDst,
                              StdPicture &tx,
                              int xSrc, int ySrc,
                              double rotateAngle, SDL_Point *center, unsigned int flip,
                              float red, float green, float blue, float alpha, int depth)
{
    renderTextureI(Maths::iRound(xDst),
                   Maths::iRound(yDst),
                   Maths::iRound(wDst),
                   Maths::iRound(hDst),
                   tx,
                   xSrc,
                   ySrc,
                   rotateAngle, center, flip,
                   red, green, blue, alpha, depth);
}

void FrmMain::renderTexture(int xDst, int yDst, StdPicture &tx, float red, float green, float blue, float alpha, int depth)
{
    C2D_DrawImage_Custom_Basic(tx.image, xDst, yDst, depth, 0);
}

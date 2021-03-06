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

#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <string>
#include <set>

#ifndef __EMSCRIPTEN__
#include <deque>
#endif

#include "std_picture.h"
#include "cmd_line_setup.h"
#include "second_screen.h"

#include <citro3d.h>
#include <citro2d.h>

class FrmMain
{
    std::string m_windowTitle;
    void *m_window = nullptr; // SDL_Window
    void *m_gRenderer = nullptr; // SDL_Renderer
    void  *m_tBuffer = nullptr; // SDL_Texture
    std::set<C2D_SpriteSheet> m_textureBank; // SDL_Texture
    bool m_sdlLoaded = false;
    const uint8_t *m_keyboardState = nullptr;
    touchPosition m_lastMousePosition = {0, 0};
    std::set<StdPicture*> m_bigPictures;
    uint32_t currentFrame = 0;
    int m_ri; // SDL_RendererInfo
    float depthSlider = 1.;
public:
    int ScaleWidth = 800;
    int ScaleHeight = 600;

    int MousePointer = 0;

    int numEyes = 2;

    uint32_t keys_held = 0;
    uint32_t keys_pressed = 0;
    uint32_t keys_released = 0;

    FrmMain();

    void *getWindow(); // SDL_Window

    uint8_t getKeyState(int key);

    bool initSDL(const CmdLineSetup_t &setup);
    void freeSDL();

    void show();
    void hide();
    void doEvents();
    void waitEvents();

    bool isWindowActive();
    bool hasWindowMouseFocus();

    void eventResize();
    int setFullScreen(bool fs);
    bool isSdlError();

    void toggleDebug();

    void initDraw(int screen = 0);
    void setLayer(int layer);
    void finalizeDraw();
    void repaint();
    void updateViewport();
    void resetViewport();
    void setViewport(int x, int y, int w, int h);
    void offsetViewport(int x, int y); // for screen-shaking

    StdPicture LoadPicture(std::string path);
    StdPicture lazyLoadPicture(std::string path);
    bool freeTextureMem();
    void deleteTexture(StdPicture &tx, bool lazyUnload = false);
    void clearAllTextures();

    void clearBuffer();
    void renderRect(int x, int y, int w, int h, float red, float green, float blue, float alpha = 1.f, bool filled = true);
    void renderRectBR(int _left, int _top, int _right, int _bottom, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    void renderCircle(int cx, int cy, int radius, float red = 1.f, float green = 1.f, float blue = 1.f, float alpha = 1.f, bool filled = true);

    // Similar to BitBlt, but without masks, just draw a texture or it's fragment!
private:
    void renderTexturePrivate(float xDst, float yDst, float wDst, float hDst,
                        StdPicture &tx,
                        float xSrc, float ySrc,
                        bool shadow = false);
public:
    void renderTexture(double xDst, double yDst, double wDst, double hDst,
                       StdPicture &tx,
                       unsigned int xSrc, unsigned int ySrc,
                       bool shadow = false);

    void renderTextureScale(float xDst, float yDst, float wDst, float hDst,
                        StdPicture &tx,
                        float xSrc, float ySrc, float wSrc, float hSrc,
                        bool shadow = false);

    void renderTexture(double xDst, double yDst, int wDst, int hDst,
                       StdPicture &tx,
                       unsigned int xSrc, unsigned int ySrc,
                       bool shadow = false);

    void renderTexture(int xDst, int yDst, int wDst, int hDst,
                       StdPicture &tx,
                       unsigned int xSrc, unsigned int ySrc,
                       bool shadow = false);

    void renderTexture(int xDst, int yDst, StdPicture &tx,
                       bool shadow = false);

private:

    void processEvent();
    void loadTexture(StdPicture &target, C2D_SpriteSheet &sheet);
    void loadTexture2(StdPicture &target, C2D_SpriteSheet &sheet);
    void loadTexture3(StdPicture &target, C2D_SpriteSheet &sheet);

    void lazyLoad(StdPicture &target);
    void lazyUnLoad(StdPicture &target);

    //Scale of virtual and window resolutuins
    float scale_x = 1.f;
    float scale_y = 1.f;
    //Side offsets to keep ratio
    float offset_x = 0.f;
    float offset_y = 0.f;
    //Offset to shake screen
    int viewport_offset_x = 0;
    int viewport_offset_y = 0;
    //Need to calculate relative viewport position when screen was scaled
    float viewport_scale_x = 1.0f;
    float viewport_scale_y = 1.0f;

    int viewport_x = 0;
    int viewport_y = 0;
    int viewport_w = 0;
    int viewport_h = 0;

    C3D_RenderTarget* top;
    C3D_RenderTarget* right;
    C3D_RenderTarget* bottom;
    int currentLayer = 0;
    Tex3DS_SubTexture layer_subtexs[4];
    C3D_Tex layer_texs[4];
    C2D_Image layer_ims[4];
    C3D_RenderTarget* layer_targets[4];

    SDL_Point MapToScr(int x, int y);
};

#endif // FRMMAIN_H

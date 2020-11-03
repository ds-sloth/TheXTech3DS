#include "custom_draw_image.h"
#include "SDL_supplement.h"

const C2D_ImageTint shadowTint =
{C2D_Color32(0,0,0,255), 1.,
C2D_Color32(0,0,0,255), 1.,
C2D_Color32(0,0,0,255), 1.,
C2D_Color32(0,0,0,255), 1.};

bool C2D_DrawImage_Custom(C2D_Image img, float x, float y, float w, float h, float src_x, float src_y, float src_w, float src_h, float depth, uint flip, bool shadow)
{
    const Tex3DS_SubTexture* old_subtex = img.subtex;
    // assuming not rotated (it isn't here)
    float scale_x = (old_subtex->right - old_subtex->left)/old_subtex->width;
    float scale_y = (old_subtex->bottom - old_subtex->top)/old_subtex->height;
    const Tex3DS_SubTexture new_subtex = {
        src_w,
        src_h,
        old_subtex->left + src_x*scale_x,
        old_subtex->top + src_y*scale_y,
        old_subtex->left + (src_x + src_w)*scale_x,
        old_subtex->top + (src_y + src_h)*scale_y,
    };
    img.subtex = &new_subtex;

    bool result;
    if (shadow)
        result = C2D_DrawImageAt(img, x, y, depth, &shadowTint, (flip & SDL_FLIP_HORIZONTAL) ? -1. : 1., (flip & SDL_FLIP_VERTICAL) ? -1. : 1.);
    else
        result = C2D_DrawImageAt(img, x, y, depth, nullptr, (flip & SDL_FLIP_HORIZONTAL) ? -1. : 1., (flip & SDL_FLIP_VERTICAL) ? -1. : 1.);
    img.subtex = old_subtex;
    return result;
}


bool C2D_DrawImage_Custom_Basic(C2D_Image img, float x, float y, float depth, bool shadow)
{
    return C2D_DrawImageAt(img, x, y, depth);
}

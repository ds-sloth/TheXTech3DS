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
    // C2Di_Context* ctx = C2Di_GetContext();
    // if (!(ctx->flags & C2DiF_Active))
    //     return false;
    // if (6 > (ctx->vtxBufSize - ctx->vtxBufPos))
    //     return false;

    // C2Di_SetCircle(false);
    // C2Di_SetTex(img.tex);
    // C2Di_Update();

    // // Calculate positions
    // float w = img.subtex->width;
    // float h = img.subtex->height;

    // float TopLeft[2], TopRight[2], BotLeft[2], BotRight[2];
    // TopLeft[0] = x;
    // TopLeft[1] = y;
    // TopRight[0] = x+w;
    // TopRight[1] = y;
    // BottomLeft[0] = x;
    // BottomLeft[1] = y+h;
    // BottomRight[0] = x+w;
    // BottomRight[1] = y+h;

    // // Calculate texcoords
    // float tcTopLeft[2], tcTopRight[2], tcBotLeft[2], tcBotRight[2];
    // Tex3DS_SubTextureTopLeft    (img.subtex, &tcTopLeft[0],  &tcTopLeft[1]);
    // Tex3DS_SubTextureTopRight   (img.subtex, &tcTopRight[0], &tcTopRight[1]);
    // Tex3DS_SubTextureBottomLeft (img.subtex, &tcBotLeft[0],  &tcBotLeft[1]);
    // Tex3DS_SubTextureBottomRight(img.subtex, &tcBotRight[0], &tcBotRight[1]);


    // // Calculate colors
    // static const C2D_Tint s_defaultTint = { 0xFF<<24, 0.0f };
    // // const C2D_Tint* tintTopLeft  = tint ? &tint->corners[C2D_TopLeft]  : &s_defaultTint;
    // // const C2D_Tint* tintTopRight = tint ? &tint->corners[C2D_TopRight] : &s_defaultTint;
    // // const C2D_Tint* tintBotLeft  = tint ? &tint->corners[C2D_BotLeft]  : &s_defaultTint;
    // // const C2D_Tint* tintBotRight = tint ? &tint->corners[C2D_BotRight] : &s_defaultTint;
    // const C2D_Tint* tintTopLeft  = &s_defaultTint;
    // const C2D_Tint* tintTopRight = &s_defaultTint;
    // const C2D_Tint* tintBotLeft  = &s_defaultTint;
    // const C2D_Tint* tintBotRight = &s_defaultTint;

    // // Draw triangles
    // C2Di_AppendVtx(topLeft[0],  topLeft[1],  depth, tcTopLeft[0],  tcTopLeft[1],  0, tintTopLeft->blend,  tintTopLeft->color);
    // C2Di_AppendVtx(botLeft[0],  botLeft[1],  depth, tcBotLeft[0],  tcBotLeft[1],  0, tintBotLeft->blend,  tintBotLeft->color);
    // C2Di_AppendVtx(botRight[0], botRight[1], depth, tcBotRight[0], tcBotRight[1], 0, tintBotRight->blend, tintBotRight->color);

    // C2Di_AppendVtx(topLeft[0],  topLeft[1],  depth, tcTopLeft[0],  tcTopLeft[1],  0, tintTopLeft->blend,  tintTopLeft->color);
    // C2Di_AppendVtx(botRight[0], botRight[1], depth, tcBotRight[0], tcBotRight[1], 0, tintBotRight->blend, tintBotRight->color);
    // C2Di_AppendVtx(topRight[0], topRight[1], depth, tcTopRight[0], tcTopRight[1], 0, tintTopRight->blend, tintTopRight->color);

    // return true;
}

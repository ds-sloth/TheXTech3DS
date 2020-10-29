#include "custom_draw_image.h"
#include "SDL_supplement.h"

bool C2D_DrawImage_Custom(C2D_Image img, float x, float y, float w, float h, float src_x, float src_y, float src_w, float src_h, float depth, uint flip, uint32_t tint)
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
    // float TopLeft[2], TopRight[2], BotLeft[2], BotRight[2];
    // TopLeft[0] = x;
    // TopLeft[1] = y;
    // TopRight[0] = x+w;
    // TopRight[1] = y;
    // BotLeft[0] = x;
    // BotLeft[1] = y+h;
    // BotRight[0] = x+w;
    // BotRight[1] = y+h;

    // // Calculate texcoords
    // float tcTopLeft[2], tcTopRight[2], tcBotLeft[2], tcBotRight[2];
    // Tex3DS_SubTextureTopLeft    (img.subtex, &tcTopLeft[0],  &tcTopLeft[1]);
    // Tex3DS_SubTextureTopRight   (img.subtex, &tcTopRight[0], &tcTopRight[1]);
    // Tex3DS_SubTextureBottomLeft (img.subtex, &tcBotLeft[0],  &tcBotLeft[1]);
    // Tex3DS_SubTextureBottomRight(img.subtex, &tcBotRight[0], &tcBotRight[1]);

    // if (!Tex3DS_SubTextureRotated) {
    //     tcTopLeft[0] += src_x;
    //     tcTopLeft[1] += src_y;
    //     tcTopRight[0] += src_x + src_w - img.subtex->width;
    //     tcTopRight[1] += src_y;
    //     tcBottomLeft[0] += src_x;
    //     tcBottomLeft[1] += src_y + src_h - img.subtex->height;
    //     tcBottomRight[0] += src_x + src_w - img.subtex->width;
    //     tcBottomRight[1] += src_y + src_h - img.subtex->height;
    // }
    // // still TODO for the non-rotated case

    // // Perform flip if needed
    // // there are a lot of instructions here I can eliminate......
    // if (flip & SDL_FLIP_VERTICAL)
    // {
    //     C2Di_SwapUV(tcTopLeft, tcTopRight);
    //     C2Di_SwapUV(tcBotLeft, tcBotRight);
    // }
    // if (flip & SDL_FLIP_HORIZONTAL)
    // {
    //     C2Di_SwapUV(tcTopLeft, tcBotLeft);
    //     C2Di_SwapUV(tcTopRight, tcBotRight);
    // }

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


bool C2D_DrawImage_Custom_Basic(C2D_Image img, float x, float y, float depth, uint32_t tint)
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

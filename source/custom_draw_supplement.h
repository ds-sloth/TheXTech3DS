#include "citro2d.h"

inline bool C2D_DrawImage_Custom(C2D_Image img, float x, float y, float src_x, float src_y, float src_w, float src_h, bool shadow)
{
    C2Di_Context* ctx = C2Di_GetContext();
    if (!(ctx->flags & C2DiF_Active))
        return false;
    if (6 > (ctx->vtxBufSize - ctx->vtxBufPos))
        return false;

    C2Di_SetTex(img.tex);
    C2Di_Update();

    // Calculate texcoords
    float tex_scale_x = (img.subtex->right - img.subtex->left)/img.subtex->width;
    float tex_scale_y = (img.subtex->bottom - img.subtex->top)/img.subtex->height;
    float u1 = img.subtex->left + src_x*tex_scale_x;
    float u2 = img.subtex->left + (src_x+src_w)*tex_scale_x;
    float v1 = img.subtex->top + src_y*tex_scale_y;
    float v2 = img.subtex->top + (src_y+src_h)*tex_scale_y;

    static const C2D_Tint s_defaultTint = { (uint32_t) 0xFF<<24, 0.0f };
    static const C2D_Tint s_shadowTint = {C2D_Color32(0,0,0,255), 1.};
    if (!shadow)
    {
        C2Di_AppendVtx(x,       y,       0.f, u1, v1, 0, s_defaultTint.blend, s_defaultTint.color);
        C2Di_AppendVtx(x,       y+src_h, 0.f, u1, v2, 0, s_defaultTint.blend, s_defaultTint.color);
        C2Di_AppendVtx(x+src_w, y+src_h, 0.f, u2, v2, 0, s_defaultTint.blend, s_defaultTint.color);

        C2Di_AppendVtx(x,       y,       0.f, u1, v1, 0, s_defaultTint.blend, s_defaultTint.color);
        C2Di_AppendVtx(x+src_w, y+src_h, 0.f, u2, v2, 0, s_defaultTint.blend, s_defaultTint.color);
        C2Di_AppendVtx(x+src_w, y,       0.f, u2, v1, 0, s_defaultTint.blend, s_defaultTint.color);
    }
    else
    {
        C2Di_AppendVtx(x,       y,       0.f, u1, v1, 0, s_shadowTint.blend, s_shadowTint.color);
        C2Di_AppendVtx(x,       y+src_h, 0.f, u1, v2, 0, s_shadowTint.blend, s_shadowTint.color);
        C2Di_AppendVtx(x+src_w, y+src_h, 0.f, u2, v2, 0, s_shadowTint.blend, s_shadowTint.color);

        C2Di_AppendVtx(x,       y,       0.f, u1, v1, 0, s_shadowTint.blend, s_shadowTint.color);
        C2Di_AppendVtx(x+src_w, y+src_h, 0.f, u2, v2, 0, s_shadowTint.blend, s_shadowTint.color);
        C2Di_AppendVtx(x+src_w, y,       0.f, u2, v1, 0, s_shadowTint.blend, s_shadowTint.color);
    }

    return true;
}

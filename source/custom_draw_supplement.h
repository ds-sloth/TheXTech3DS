const C2D_ImageTint shadowTint =
{C2D_Color32(0,0,0,255), 1.,
C2D_Color32(0,0,0,255), 1.,
C2D_Color32(0,0,0,255), 1.,
C2D_Color32(0,0,0,255), 1.};

inline bool C2D_DrawImage_Custom(C2D_Image img, float x, float y, float src_x, float src_y, float src_w, float src_h, bool shadow)
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
        result = C2D_DrawImageAt(img, x, y, 0.f, &shadowTint);
    else
        result = C2D_DrawImageAt(img, x, y, 0.f);
    img.subtex = old_subtex;
    return result;
}

inline bool C2D_DrawImage_Custom(C2D_Image img, float x, float y, float w, float h,
    float src_x, float src_y, float src_w, float src_h, bool shadow)
{
    const Tex3DS_SubTexture* old_subtex = img.subtex;
    // assuming not rotated (it isn't here)
    float scale_x = (old_subtex->right - old_subtex->left)/old_subtex->width;
    float scale_y = (old_subtex->bottom - old_subtex->top)/old_subtex->height;
    const Tex3DS_SubTexture new_subtex = {
        w,
        h,
        old_subtex->left + src_x*scale_x,
        old_subtex->top + src_y*scale_y,
        old_subtex->left + (src_x + src_w)*scale_x,
        old_subtex->top + (src_y + src_h)*scale_y,
    };
    img.subtex = &new_subtex;

    bool result;
    if (shadow)
        result = C2D_DrawImageAt(img, x, y, 0.f, &shadowTint);
    else
        result = C2D_DrawImageAt(img, x, y, 0.f);
    img.subtex = old_subtex;
    return result;
}

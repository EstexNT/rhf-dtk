#ifndef RVL_SDK_GX_PIXEL_H
#define RVL_SDK_GX_PIXEL_H
#include <revolution/GX/GXTypes.h>
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

void GXSetBlendMode(GXBlendMode mode, GXBlendFactor src, GXBlendFactor dst,
    GXLogicOp op);

void GXSetColorUpdate(GXBool enable);
    
void GXSetZMode(GXBool enableTest, GXCompare func, GXBool enableUpdate);

void GXSetPixelFmt(GXPixelFmt pixelFmt, GXZFmt zFmt);

#ifdef __cplusplus
}
#endif
#endif

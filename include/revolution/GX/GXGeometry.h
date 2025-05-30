#ifndef RVL_SDK_GX_GEOMETRY_H
#define RVL_SDK_GX_GEOMETRY_H
#include <revolution/GX/GXTypes.h>
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

void GXBegin(GXPrimitive prim, GXVtxFmt fmt, u16 verts);
inline void GXEnd(void) {}

void GXSetCullMode(GXCullMode mode);

#ifdef __cplusplus
}
#endif
#endif

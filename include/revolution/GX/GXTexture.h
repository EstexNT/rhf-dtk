#ifndef RVL_SDK_GX_TEXTURE_H
#define RVL_SDK_GX_TEXTURE_H
#include <types.h>

#include <revolution/GX/GXTypes.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GXTexObj {
private:
    u32 data[8];
} GXTexObj;
typedef struct _GXTlutObj {
private:
    u8 data[0x0C];
} GXTlutObj;

typedef struct _GXTexRegion {
private:
    u8 data[16];
} GXTexRegion;
typedef struct _GXTlutRegion {
private:
    u8 data[16];
} GXTlutRegion;

typedef GXTexRegion* (*GXTexRegionCallback)(const GXTexObj* pObj,
                                            GXTexMapID map);

typedef GXTlutRegion* (*GXTlutRegionCallback)(u32 id);

void __GXSetSUTexRegs(void);

void GXInitTexObj(GXTexObj* obj, void* image, u16 w, u16 h, GXTexFmt fmt,
                  GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, GXBool mipmap);
void GXInitTexObjCI(GXTexObj*, void*, u16, u16, GXTexFmt, GXTexWrapMode,
                    GXTexWrapMode, GXBool, u32);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
                     f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
                     GXBool do_edge_lod, GXAnisotropy max_aniso);

void GXGetTexObjLODAll(GXTexObj* obj, GXTexFilter* min_filt,
                       GXTexFilter* mag_filt, f32* minLod, f32* maxLod,
                       f32* lodBias, GXBool* biasClampEnable,
                       GXBool* edgeLodEnable, GXAnisotropy* anisotropy);

GXTexWrapMode GXGetTexObjWrapS(GXTexObj* obj);
GXTexWrapMode GXGetTexObjWrapT(GXTexObj* obj);

u16 GXGetTexObjWidth(const GXTexObj* obj);
u16 GXGetTexObjHeight(const GXTexObj* obj);
GXTexFmt GXGetTexObjFmt(const GXTexObj* obj);
GXBool GXGetTexObjMipMap(const GXTexObj* obj);

void GXLoadTexObj(const GXTexObj*, GXTexMapID);

u32 GXGetTexObjTlut(GXTexObj*);

void GXInitTlutObj(GXTlutObj*, void*, GXTlutFmt, u16);

void GXLoadTlut(GXTlutObj*, GXTlut);

void GXInvalidateTexAll(void);

void GXInitTexCacheRegion(GXTexRegion* pRegion, GXBool r4, u32 addrTMemEven,
                          u32 sizeTMemEven, u32 addrTMemOdd, u32 sizeTMemOdd);

void GXInitTlutRegion(GXTlutRegion* pRegion, u32 addrTMem, u32 sizeTMem);

GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback callback);
GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback callback);

u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, GXBool mipmap,
                       u8 max_lod);

void GXInitTexObjFilter(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt);

#ifdef __cplusplus
}
#endif
#endif
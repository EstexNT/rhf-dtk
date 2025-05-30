#ifndef RVL_SDK_TPL_H
#define RVL_SDK_TPL_H
#include <revolution/GX.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct TPLHeader {
    u16 height;          // at 0x0
    u16 width;           // at 0x2
    u32 format;          // at 0x4
    char* data;          // at 0x8
    GXTexWrapMode wrapS; // at 0xC
    GXTexWrapMode wrapT; // at 0x10
    GXTexFilter minFilt; // at 0x14
    GXTexFilter magFilt; // at 0x18
    f32 lodBias;         // at 0x1C
    u8 edgeLodEnable;    // at 0x20
    u8 minLod;           // at 0x21
    u8 maxLod;           // at 0x22
    u8 unpacked;         // at 0x23
} TPLHeader;

typedef struct TPLClutHeader {
    u16 numEntries;   // at 0x0
    u8 unpacked;      // at 0x1
    u8 padding;       // at 0x2
    GXTlutFmt format; // at 0x4
    char* data;       // at 0x8
} TPLClutHeader;

typedef struct TPLDescriptor {
    TPLHeader* texHeader;      // at 0x0
    TPLClutHeader* clutHeader; // at 0x4
} TPLDescriptor;

typedef struct TPLPalette {
    u32 version;                // at 0x0
    u32 numImages;              // at 0x4
    TPLDescriptor* descriptors; // at 0x8
} TPLPalette;

void TPLBind(TPLPalette* pal);
TPLDescriptor* TPLGet(TPLPalette* pal, u32 id);

void TPLGetGXTexObjFromPalette(TPLPalette*, GXTexObj*, u32);
void TPLGetGXTexObjFromPaletteCI(TPLPalette*, GXTexObj*, GXTlutObj*, int, u32);

#ifdef __cplusplus
}
#endif
#endif
#ifndef RVL_SDK_GX_FIFO_H
#define RVL_SDK_GX_FIFO_H
#include <revolution/GX/GXTypes.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GXFifoObj {
private:
    u32 data[32];
} GXFifoObj;

void GXGetGPStatus(u8*, u8*, u8*, u8*, u8*);

void GXSetCPUFifo(GXFifoObj*);
BOOL GXGetCPUFifo(GXFifoObj*);

u32 GXGetFifoCount(GXFifoObj*);
u8 GXGetFifoWrap(GXFifoObj*);

#ifdef __cplusplus
}
#endif
#endif
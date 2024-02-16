#ifndef RVL_SDK_WPAD_H
#define RVL_SDK_WPAD_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*WPADAlloc)(u32);
typedef u8 (*WPADFree)(void *);



void WPADRegisterAllocator(WPADAlloc, WPADFree);
u32 WPADGetWorkMemorySize(void);

u8 WPADGetSensorBarPosition(void);

#ifdef __cplusplus
}
#endif
#endif

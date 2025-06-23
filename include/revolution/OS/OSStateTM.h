#ifndef RVL_SDK_OS_STATETM_H
#define RVL_SDK_OS_STATETM_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*OSStateCallback)(void);

OSStateCallback OSSetResetCallback(OSStateCallback callback);
OSStateCallback OSSetPowerCallback(OSStateCallback callback);

#ifdef __cplusplus
}
#endif
#endif
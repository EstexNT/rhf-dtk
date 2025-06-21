#ifndef RVL_SDK_OS_H
#define RVL_SDK_OS_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

void OSInit(void);

void OSRegisterVersion(const char* ver);

#ifdef __cplusplus
}
#endif
#endif
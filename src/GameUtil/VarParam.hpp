#ifndef GAMEUTIL_CVARPARAMMANAGER_HPP
#define GAMEUTIL_CTICKFLOWMANAGER_HPP

#include <revolution/types.h>
#include "Singleton.hpp"

#include "Mem.hpp"

class CVarParam;

class CVarParamManager : public TSingleton<CVarParamManager> {
public:
    virtual void _08(void);
    virtual ~CVarParamManager(void);
    virtual void _10(s32);
    virtual void _14(void);

    CVarParamManager(void);

    void fn_801ED2AC(void);

private:
    static void fn_801ED44C(void);

    CVarParam *mFirstVarParam;
    s32 mDisplayMode;
    u8 mUnk0C;

    u8 *mHeapStart;
    MEMiHeapHead *mExpHeap;
};

extern CVarParamManager *gVarParamManager;

#endif
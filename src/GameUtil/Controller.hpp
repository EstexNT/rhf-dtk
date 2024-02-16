#ifndef GAMEUTIL_CCONTROLLERMANAGER_HPP
#define GAMEUTIL_CCONTROLLERMANAGER_HPP

#include <revolution/types.h>
#include <revolution/OS.h>
#include <revolution/MEM.h>
#include <revolution/PAD.h>
#include "TSingleton.hpp"


class CController {
public:

    virtual ~CController(void) {

    }
    virtual void _0C(void);
    virtual void _10(void);
    virtual void _14(void);
    virtual u8 _18(void) {
        return 0; // TODO
    }
    virtual bool _1C(void) {
        return false; // TODO
    }
    virtual bool _20(void) {
        return false; // TODO
    }
    virtual bool _24(void) {
        return false; // TODO
    }
    virtual bool _28(void) {
        return false; // TODO
    }
    virtual bool _2C(void) {
        return false; // TODO
    }
    virtual bool _30(void) {
        return false; // TODO
    }
    virtual bool _34(void) {
        return false; // TODO
    }
    virtual bool _38(void) {
        return false; // TODO
    }
    virtual bool _3C(void) {
        return false; // TODO
    }
    virtual void _40(const char *, u32);
    virtual void _44(void);
    virtual bool _48(void) {
        return false; // TODO
    }
    virtual void _4C(void);
    
    CController(s32);

};

class CNullController : public CController {
public:

    virtual ~CNullController(void) {

    }

    virtual u8 _18(void);
    virtual bool _24(void);
    virtual bool _28(void);
    virtual bool _2C(void);
    virtual bool _30(void);
    virtual bool _34(void);
    virtual bool _38(void);
    virtual bool _3C(void);

    CNullController(s32 arg0) : CController(arg0) {

    }
private:

    u8 pad04[0x13b4];
};

class CGCController {
public:

    virtual ~CGCController(void);
    virtual void _0C(void);
    virtual void _10(void) {

    }

    CGCController(s32 i) {
        unk04 = i;
        unk10 = 10;
        unk11 = 4;
    }

    void setUnk08(PADStatus *arg0) {
        unk08 = arg0;
    }
    void setUnk0C(PADStatus *arg0) {
        unk0C = arg0;
    }

private:
    s32 unk04;
    PADStatus *unk08;
    PADStatus *unk0C;
    u8 unk10;
    u8 unk11;
    u32 pad14;
};


// TODO: move this somewhere else
template <typename T>
struct Lock {
    Lock(T arg0) {
        inter = OSDisableInterrupts();
    }
    ~Lock(void) {
        OSRestoreInterrupts(inter);
    }

    BOOL inter;
};

class CControllerManager : public TSingleton<CControllerManager> {
public:

    virtual void _08(void);
    virtual ~CControllerManager(void);
    virtual void _10(CController *(s32));
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void);

    CControllerManager(void);

    CController *fn_801D5FF0(s32 idx);
    CGCController *fn_801D6000(s32 idx);

    void *doAlloc(u32 size) {
        // TODO: doesn't match when using Lock..
        BOOL inter = OSDisableInterrupts();
        void *alloc = MEMAllocFromAllocator(&unk1C, size);
        OSRestoreInterrupts(inter);
        return alloc;
    }

    u8 doFree(void *alloc) {
        Lock<void *> lock(alloc);
        MEMFreeToAllocator(&unk1C, alloc);
        return true;
    }
private:

    CController *unk04[4];
    CNullController *unk14;
    MEMiHeapHead *unk18;
    MEMAllocator unk1C;
    u8 *unk2C;
    CGCController *unk30[4];
    PADStatus unk40[4];
    PADStatus unk70[4];

    static void *fn_801D5950(u32);
    static u8 fn_801D59B0(void *);
};

extern CControllerManager *gControllerManager;

#endif
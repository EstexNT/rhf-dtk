#ifndef GAMEUTIL_CINPUTCHECKMANAGER_HPP
#define GAMEUTIL_CINPUTCHECKMANAGER_HPP

#include <revolution/types.h>
#include <revolution/MEM.h>
#include "TSingleton.hpp"
#include "CInputChecker.hpp"
#include "CTickFlowManager.hpp"
#include "CCheckPointManager.hpp"

class CInputCheckManager : public TSingleton<CInputCheckManager> {
public:

    virtual void _08(void);
    virtual ~CInputCheckManager(void);
    virtual void _10(u32);
    virtual void _14(void);

    CInputCheckManager(void);
    void fn_801E8A08(void);
    void fn_801E8BD0(void);
    void *fn_801E9144(u32);
    void fn_801E9150(void *);
    void fn_801E9158(CInputChecker *);
    void fn_801E9204(void);
    void fn_801E923C(u32);
    bool fn_801E93E0(u32, f32, f32);
    void fn_801E9474(void);
    void fn_801E9488(u32);
    u32 fn_801E94D4(void);
    void fn_801E94E8(u32);
    void fn_801E9604(bool);
    void fn_801E960C(void);
    void fn_801E9C30(bool);
    void fn_801E9C38(f32);
    void fn_801E9C40(void);
    void fn_801E9D58(u32);
    void fn_801E9D68(u32);
    void fn_801E9D7C(CInputChecker *);
    void fn_801E9D80(char *);
    void fn_801E9D84(void);
    void fn_801E9D88(void);
    void fn_801E9D8C(void);

    u8 getUnk42E(void) {
        return unk42E;
    }
private:

    u8 *unk04;
    MEMiHeapHead *unk08;
    CInputChecker *unk0C;
    struct UnkSub {
        u8 unk0;
        u32 unk4;
        f32 unk8;
        f32 unkC;
    } unk10[0x40];
    u32 unk410;
    void (*unk414)(void);
    void (*unk418)(u32);
    u8 unk41C;
    u8 pad41D[0x420 - 0x41d];
    u32 unk420;
    u32 unk424;
    u8 unk428;
    u8 unk429;
    u8 unk42A;
    u8 unk42B;
    u8 unk42C;
    u8 unk42D;
    u8 unk42E;
    u8 unk42F;
    u32 unk430[16];
    f32 unk470;
    f32 unk474[4];
    u8 unk484;
    u8 pad485[7];
    u8 unk48C;
    u8 unk48D;
    u8 pad48E[0xe];
    u8 unk49C;
    f32 unk4A0;
    u32 unk4A4[256];
    s32 (*unk8A4)(u32);

    static void fn_801E8118(void);
    static void fn_801E8560(void);
    static s32 fn_801E85AC(u32);

    void resetUnk0C(void) {
        for (CInputChecker *cur = unk0C, *next; cur != 0; cur = next) {
            next = (CInputChecker *)cur->mNext;
            if (!cur->_18()) {
                continue;
            }
            if (cur == unk0C) {
                unk0C = (CInputChecker *)cur->mNext;
            }
            cur->removeCurrent();
        }
        for (int i = 0; i < 4; i++) {
            if (!(unk474[i] > (f64)0)) {
                continue;
            }
            unk474[i] -= gTickFlowManager->fn_801E2698();
            if (unk474[i] <= (f64)0) {
                unk474[i] = 0.f;
            }
        }
    }

    void resetUnk10(void) {
        for (int i = 0; i < (s32)ARRAY_LENGTH(unk10); i++) {
            if (!unk10[i].unk0) {
                continue;
            }
            
            unk10[i].unk8 += gTickFlowManager->fn_801E2698();
            if (!(unk10[i].unk8 > unk10[i].unkC)) {
                continue;
            }
            unk10[i].unk0 = 0;
            if (unk418) {
                unk418(unk4A4[unk10[i].unk4]);
            }
            if (!gCheckPointManager->getUnkDD()) {
                continue;
            }
            if (unk428 >= 6) {
                continue;
            }
            unk428++;
        }
    }

    void resetUnk4A4(void) {
        for (int i = 0; i < (s32)ARRAY_LENGTH(unk4A4); i++) {
            unk4A4[i] = i;
        }
    }

    u32 checkUnk430(u32 arg0) {
        for (int i = 0; i < (s32)ARRAY_LENGTH(unk430); i++) {
            if (unk430[i] == arg0) {
                return 1;
            }
        }
        return 0;
    }

    u32 unkCheck(u32 arg0) {
        if (unk42F) {
            return 1;
        }
        return checkUnk430(arg0);
    }

    void unkInline(u8 arg0) {
        if (gCheckPointManager->getUnkDD()) {
            if (!arg0) {
                arg0 = unk428 * 5;
            }
            unk428 = 0;
            unk420 += arg0;
            unk424++;
        }
    }
};

extern CInputCheckManager *gInputCheckManager;

#endif
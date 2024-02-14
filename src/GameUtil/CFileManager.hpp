#ifndef GAMEUTIL_CFILEMANAGER_HPP
#define GAMEUTIL_CFILEMANAGER_HPP

#include <revolution/types.h>
#include <revolution/DVD.h>
#include <revolution/ARC.h>
#include "Mem.hpp"
#include "TSingleton.hpp"

struct CFileManager_sub {
    u8 pad00[0x44];
};

struct CFileManager_sub1 {
    DVDFileInfo *unk0;
    ARCHandle unk4;
    u8 *unk20;
    EHeapMEM unk24;
    u16 unk28;
    bool unk2A;
    s32 unk2C;
};

extern "C" void fn_801D7538(s32);

class CFileManager : public TSingleton<CFileManager> {
public:

    virtual void _08(void);
    virtual ~CFileManager(void);
    virtual void _10(s32, s32);
    virtual void _14(void);

    CFileManager(void);

    void fn_801D3C2C(const char *file);
    char *fn_801D3C44(void);
    void *fn_801D3C4C(const char *file, EHeapMEM heap, s32 alignment);
    bool fn_801D3D58(void);
    void fn_801D3D94(void);
    void fn_801D3E94(void);
    void fn_801D3F94(s32 idx, const char *file, EHeapMEM heap, s32 alignment);
    void fn_801D412C(s32, DVDFileInfo *);
    void fn_801D41CC(s32 idx);
    u32 fn_801D422C(s32 idx, const char *file);
    void *fn_801D4270(s32 idx, const char *file);
    void *fn_801D42CC(s32 idx);
    bool fn_801D42E0(s32 idx);
    bool fn_801D42FC(s32 idx);
    bool fn_801D431C(void);
    void fn_801D4364(s32 idx);
    void fn_801D443C(void);
    void fn_801D4544(void);
    void fn_801D49D4(void);

    static void *fn_801D461C(void *, u32, EHeapMEM, s32);

    inline s32 getFileInfoIdx(DVDFileInfo *fileInfo) {
        s32 temp_r6 = -1;
        for (int i = 0; i < unk08; i++) {
            if ((unk0C + i) == fileInfo) {
                temp_r6 = i;
                break;
            }
        }
        return temp_r6;
    }
    inline void checkDrive(void) {
        s32 driveStatus = DVDGetDriveStatus();
        switch (driveStatus) {
            case DVD_STATE_NO_DISK:
            case DVD_STATE_WRONG_DISK:
            case DVD_STATE_RETRY:
                if (unk34C) {
                    unk34C();
                }
                fn_801D7538(driveStatus);
                if (unk350) {
                    unk350();
                }
        }
    }
private:

    static char lbl_803D5C48[64];

    char unk04[4];
    s32 unk08;
    DVDFileInfo *unk0C;
    CFileManager_sub *unk10;
    u8 *unk14;
    s32 unk18;
    CFileManager_sub1 *unk1C;
    u8 pad20[0x10];
    OSThread unk30;
    u32 *unk348;
    void (*unk34C)(void);
    void (*unk350)(void);

    static void fn_801D392C(s32, DVDFileInfo *); // DVDAsyncCallback
    static void fn_801D3988(s32, DVDFileInfo *); // DVDAsyncCallback
    static void *fn_801D46A4(void *, u32, s32, EHeapMEM, s32);
    static void *fn_801D47B8(void *);
    static bool fn_801D47F8(void *in, void *out, u32 arg2, u32 size, s32 arg4, u32 arg5);
};

extern CFileManager *gFileManager;

#endif

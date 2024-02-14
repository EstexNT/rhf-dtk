#ifndef GAMEUTIL_CFILEMANAGER_HPP
#define GAMEUTIL_CFILEMANAGER_HPP

#include <revolution/types.h>
#include <revolution/DVD.h>
#include "Mem.hpp"
#include "TSingleton.hpp"

struct CFileManager_sub {
    u8 pad00[0x44];
};

struct CFileManager_sub1 {
    DVDFileInfo *unk0;
    u8 pad04[0x1c];
    void *unk20;
    EHeapMEM unk24;
    u16 unk28;
    bool unk2A;
    u32 unk2C;
};

extern "C" void fn_801D7538(s32);

class CFileManager : public TSingleton<CFileManager> {
public:

    virtual void _08(void);
    virtual ~CFileManager(void);
    virtual void _10(s32, s32);
    virtual void _14(void);

    CFileManager(void);

    void fn_801D3C2C(const char *);
    char *fn_801D3C44(void);
    void *fn_801D3C4C(const char *name, EHeapMEM heap, s32 alignment);
    bool fn_801D3D58(void);
    void fn_801D3D94(void);
    void fn_801D3E94(void);
    void fn_801D3F94(s32 idx, const char *fname, EHeapMEM heap, s32 alignment);
    void fn_801D412C(s32, DVDFileInfo *);
    void fn_801D41CC(s32 idx);
    
    void fn_801D4544(void);

    void fn_801D49D4(void);

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

    char unk04[4]; // mLocaleFolder
    s32 unk08;
    DVDFileInfo *unk0C;
    CFileManager_sub *unk10;
    u8 *unk14;
    s32 unk18;
    CFileManager_sub1 *unk1C;
    u8 pad20[0x328];
    u32 *unk348;
    void (*unk34C)(void);
    void (*unk350)(void);

    static void fn_801D392C(s32, DVDFileInfo *); // DVDAsyncCallback
    static void fn_801D3988(s32, DVDFileInfo *); // DVDAsyncCallback
};

extern CFileManager *gFileManager;

#endif
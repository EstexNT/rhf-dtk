#include "FileManager.hpp"
#include <string.h>

char CFileManager::lbl_803D5C48[64];

void CFileManager::fn_801D392C(s32 result, DVDFileInfo *fileInfo) {
    s32 temp_r6 = gFileManager->getFileInfoIdx(fileInfo);
    if (result == DVD_RESULT_FATAL_ERROR) {
        return;
    }
    gFileManager->unk14[temp_r6] = 0;
}

void CFileManager::fn_801D3988(s32 result, DVDFileInfo *fileInfo) {
    gFileManager->fn_801D412C(result, fileInfo);
}

CFileManager::CFileManager(void) {

}

CFileManager::~CFileManager(void) {
    _08();
}

void CFileManager::_10(s32 arg1, s32 arg2) {
    unk18 = arg2;
    unk08 = arg1;

    unk0C = new (eHeap_MEM2, 32) DVDFileInfo[unk08];
    unk10 = new (eHeap_MEM2, 32) CFileManager_sub[unk08];
    unk14 = new (eHeap_MEM2, 32) u8[unk08];
    unk1C = new (eHeap_MEM2, 32) CFileManager_sub1[unk18];
    unk348 = new (eHeap_MEM2, 32) u32[0xa00];
}

void CFileManager::_08(void) {
    delete[] unk0C;
    delete[] unk10;
    delete[] unk14;
    delete[] unk1C;
}

void CFileManager::_14(void) {
    DVDInit();
    for (int i = 0; i < unk08; i++) {
        unk14[i] = 0;
    }
    for (int i = 0; i < unk18; i++) {
        unk1C[i].unk0 = 0;
        unk1C[i].unk20 = 0;
        unk1C[i].unk2C = 0;
    }
    unk34C = 0;
    unk350 = 0;
}

extern "C" int sprintf(char *, const char *, ...); // TODO: move to a proper header

void CFileManager::fn_801D3C2C(const char *arg1) {
    sprintf(unk04, "%s", arg1);
}

char *CFileManager::fn_801D3C44(void) {
    return unk04;
}

void *CFileManager::fn_801D3C4C(const char *file, EHeapMEM heap, s32 alignment) {
    sprintf(lbl_803D5C48, "%s%s", gFileManager->fn_801D3C44(), file);
    s32 temp_r29 = -1;
    for (int i = 0; i < unk08; i++) {
        if (unk14[i] == 0) {
            temp_r29 = i;
            break;
        }
    }

    DVDOpen(lbl_803D5C48, unk0C + temp_r29);
    s32 size = ROUND_UP(unk0C[temp_r29].length, 32);
    void *alloc = new (heap, alignment) u8[size];
    DCInvalidateRange(alloc, size);
    DVDReadAsyncPrio((unk0C + temp_r29), alloc, size, 0, CFileManager::fn_801D392C, 2);
    unk14[temp_r29] = 1;
    return alloc;
}

bool CFileManager::fn_801D3D58(void) {
    for (int i = 0; i < unk08; i++) {
        if (unk14[i]) {
            return true;
        }
    }
    return false;
}

struct TimeThing { // TODO: move this somewhere else?
    TimeThing(s32 a) {
        val = a * 10;
    }
    s64 GetMsecVal(void) {
        return 10;
    }
    s32 val;
};

void CFileManager::fn_801D3D94(void) {
    TimeThing thing = 0;
    while (fn_801D3D58()) {
        gFileManager->fn_801D49D4(); // <--TODO: regswap
        gFileManager->fn_801D4544();
        OSSleepTicks(OS_MSEC_TO_TICKS(thing.GetMsecVal()));
    }
}

void CFileManager::fn_801D3E94(void) {
    TimeThing thing = 0;
    while (fn_801D3D58()) {
        gFileManager->fn_801D49D4(); // <--TODO: regswap
        gFileManager->fn_801D4544();
        OSSleepTicks(OS_MSEC_TO_TICKS(thing.GetMsecVal()));
    }
}

void CFileManager::fn_801D3F94(s32 idx, const char *file, EHeapMEM heap, s32 alignment) {
    sprintf(lbl_803D5C48, "%s%s", gFileManager->fn_801D3C44(), file);
    s32 temp_r28 = -1;
    for (int i = 0; i < unk08; i++) {
        if (unk14[i] == 0) {
            temp_r28 = i;
            break;
        }
    }
    unk1C[idx].unk0 = unk0C + temp_r28;
    unk1C[idx].unk24 = heap;
    unk1C[idx].unk28 = fn_801D363C();
    char *temp = ".szs"; // TODO: fake match?
    unk1C[idx].unk2A = strstr(lbl_803D5C48, temp) != 0;
    unk1C[idx].unk2C = 1;
    DVDOpen(lbl_803D5C48, (unk0C + temp_r28));
    u32 size = ROUND_UP(unk0C[temp_r28].length, 32);
    unk1C[idx].unk20 = new (unk1C[idx].unk24, alignment) u8[size];
    DCInvalidateRange(unk1C[idx].unk20, size);
    DVDReadAsyncPrio((unk0C + temp_r28), unk1C[idx].unk20, size, 0, CFileManager::fn_801D3988, 2);
    unk14[temp_r28] = 1;
}

void CFileManager::fn_801D412C(s32 result, DVDFileInfo *fileInfo) {
    s32 temp_r7 = -1; // doesn't match with the inline
    for (int i = 0; i < unk08; i++) {
        if ((unk0C + i) == fileInfo) {
            temp_r7 = i;
            break;
        }
    }

    if (result == DVD_RESULT_FATAL_ERROR) {
        return;
    }

    unk14[temp_r7] = 0;
    for (int i = 0; i < unk18; i++) {
        if (unk1C[i].unk0 == fileInfo) {
            unk1C[i].unk2C = 2;
            return;
        }
    }
}

void CFileManager::fn_801D41CC(s32 idx) {
    delete[] unk1C[idx].unk20;
    unk1C[idx].unk20 = 0;
    unk1C[idx].unk2C = 0;
}

u32 CFileManager::fn_801D422C(s32 idx, const char *file) {
    ARCFileInfo fileInfo;
    ARCOpen(&unk1C[idx].unk4, file, &fileInfo);
    u32 length = ARCGetLength(&fileInfo);
    //ARCClose(&fileInfo); // why is this not present?
    return length;
}

void *CFileManager::fn_801D4270(s32 idx, const char *file) {
    ARCFileInfo fileInfo;
    ARCOpen(&unk1C[idx].unk4, file, &fileInfo);
    void *startAddr = ARCGetStartAddrInMem(&fileInfo);
    ARCClose(&fileInfo);
    return startAddr;
}

void *CFileManager::fn_801D42CC(s32 idx) {
    return unk1C[idx].unk20;
}

bool CFileManager::fn_801D42E0(s32 idx) {
    return unk1C[idx].unk2C == 0;
}

bool CFileManager::fn_801D42FC(s32 idx) {
    return unk1C[idx].unk2C == 5;
}

bool CFileManager::fn_801D431C(void) {
    bool temp_r6 = true;
    for (int i = 0; i < unk08; i++) {
        if ((unk1C[i].unk2C != 0) && (unk1C[i].unk2C != 5)) {
            temp_r6 = false;
        }
    }
    return temp_r6;
}

void CFileManager::fn_801D4364(s32 idx) {
    TimeThing thing = 0;
    while (unk1C[idx].unk2C != 5) {
        gFileManager->fn_801D49D4(); // <--TODO: regswap
        gFileManager->fn_801D4544();
        OSSleepTicks(OS_MSEC_TO_TICKS(thing.GetMsecVal()));
    }
}

void CFileManager::fn_801D443C(void) {
    TimeThing thing = 0;
    while (!fn_801D431C()) {
        gFileManager->fn_801D49D4(); // <--TODO: regswap
        gFileManager->fn_801D4544();
        OSSleepTicks(OS_MSEC_TO_TICKS(thing.GetMsecVal()));
    }
}

void CFileManager::fn_801D4544(void) {
    for (short i = 0; i < unk18; i++) {
        CFileManager_sub1 *sub1 = &unk1C[i];
        bool temp_r25 = false;

        if (sub1->unk2C == 2) {
            if (sub1->unk2A) {
                void *addr = fn_801D46A4(sub1->unk20, 1, i, sub1->unk24, -32);
                if (addr) {
                    sub1->unk20 = (u8 *)addr;
                    sub1->unk2C = 3;
                }
            } else {
                temp_r25 = true;
            }
        } else if (sub1->unk2C == 4) {
            temp_r25 = true;
        }
        if (temp_r25) {
            ARCInitHandle(sub1->unk20, &sub1->unk4);
            sub1->unk0 = 0;
            sub1->unk2C = 5;
        }
    }
}

// TODO: pretty sure this belongs to the nw4r headers
static inline u32 Nw4rSize(u8 *data) {
    return (data[4] << 0x18) | (data[5] << 0x10) | (data[6] << 8) | data[7];
}

void *CFileManager::fn_801D461C(void *data, u32 arg1, EHeapMEM heap, s32 alignment) {
    u32 temp_r31 = Nw4rSize((u8 *)data);
    u32 size = ROUND_UP(temp_r31, 32);
    void *out = new (heap, alignment) u8[size];
    fn_801D47F8(data, out, temp_r31, size, -1, arg1);
    return out;
}


struct struct_803d5c88 {
    void *unk0;
    void *unk4;
    u32 unk8;
    u32 unkC;
    s16 unk10;
    u8 unk12;
};

static struct_803d5c88 lbl_803D5C88;

void *CFileManager::fn_801D46A4(void *data, u32 arg1, s32 arg2, EHeapMEM heap, s32 alignment) {
    BOOL terminated = OSIsThreadTerminated(&gFileManager->unk30);
    if (terminated) {
        u32 temp_r26 = Nw4rSize((u8 *)data);
        u32 size = ROUND_UP(temp_r26, 32);
        if (arg2 >= 0) {
            fn_801D369C(gFileManager->unk1C[arg2].unk28);
        }
        void *alloc = new (heap, alignment) u8[size];
        if (arg2 >= 0) {
            fn_801D3644();
        }
        lbl_803D5C88.unk0 = data;
        lbl_803D5C88.unk4 = alloc;
        lbl_803D5C88.unk8 = temp_r26;
        lbl_803D5C88.unkC = size;
        lbl_803D5C88.unk10 = arg2;
        lbl_803D5C88.unk12 = arg1;
        OSCreateThread(&gFileManager->unk30, CFileManager::fn_801D47B8, &lbl_803D5C88, &gFileManager->unk348[0xa00], 0xa00 * sizeof(u32), 31, 1);
        OSResumeThread(&gFileManager->unk30);
        return alloc;
    }
    return 0;
}

void *CFileManager::fn_801D47B8(void *arg) {
    struct_803d5c88 *temp = (struct_803d5c88 *)arg;

    fn_801D47F8(temp->unk0, temp->unk4, temp->unk8, temp->unkC, temp->unk10, temp->unk12);
    return 0;
}

bool CFileManager::fn_801D47F8(void *in, void *out, u32 arg2, u32 size, s32 arg4, u32 arg5) {
    // TODO: decompile
    return false;
}

void CFileManager::fn_801D49D4(void) {
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
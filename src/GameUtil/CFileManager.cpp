#include "CFileManager.hpp"
#include <string.h>

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
        gFileManager->checkDrive(); // <-- regswap
        gFileManager->fn_801D4544();
        OSSleepTicks(OS_MSEC_TO_TICKS(thing.GetMsecVal()));
    }
}

void CFileManager::fn_801D3E94(void) {
    TimeThing thing = 0;
    while (fn_801D3D58()) {
        gFileManager->checkDrive(); // <-- regswap
        gFileManager->fn_801D4544();
        OSSleepTicks(OS_MSEC_TO_TICKS(thing.GetMsecVal()));
    }
}

void CFileManager::fn_801D3F94(s32 idx, const char *fname, EHeapMEM heap, s32 alignment) {
    sprintf(lbl_803D5C48, "%s%s", gFileManager->fn_801D3C44(), fname);
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
    char *temp = ".szs"; // fake match?
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
    s32 temp_r7 = -1; // not using the inline function here?
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


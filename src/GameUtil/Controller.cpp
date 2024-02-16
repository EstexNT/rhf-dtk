#include <revolution/PAD.h>
#include <revolution/KPAD.h>
#include <revolution/WPAD.h>
#include "Controller.hpp"
#include "Mem.hpp"

/*

        CController

*/

CController::CController(s32 i) {
    unk04 = i;
    unk136D = false;
    unk136C = false;
    unk1370 = 0;
    unk1375 = 0;
    unk1338 = 0;
    unk133C = 0;
    unk1340 = 0;
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk1344); i++) {
        unk1344[i] = 0;
    }
    unk1364 = 10;
    unk1365 = 4;
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk1354); i++) {
        if ((u16)(1 << i)) {
            unk1354[i] = 0;
        }
    }

    for (int i = 0; i < (s32)ARRAY_LENGTH(unk1354); i++) {
        if (((1 << i) & (0x800 | 0x400))) {
            unk1354[i] = 6;
        }
    }
}

void CController::_0C(void) {
    unk1398 = false;
}

void CController::_10(void) {
    
}







/* 

        CControllerManager

*/

void *CControllerManager::fn_801D5950(u32 arg0) {
    return gControllerManager->doAlloc(arg0);
}

u8 CControllerManager::fn_801D59B0(void *arg0) {
    return gControllerManager->doFree(arg0);
}

CControllerManager::CControllerManager(void) {

}

CControllerManager::~CControllerManager(void) {
    _08();
}

void CControllerManager::_10(CController *fn(s32 arg0)) {
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk04); i++) {
        unk04[i] = fn(i);
    }

    unk14 = new CNullController(-1);
    u32 wpadWorkMemSize = WPADGetWorkMemorySize() + 0x100;
    unk2C = new (eHeap_MEM2, 32) u8[wpadWorkMemSize];
    unk18 = MEMCreateExpHeap(unk2C, wpadWorkMemSize);
    MEMInitAllocatorForExpHeap(&unk1C, unk18, 32);
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk30); i++) {
        unk30[i] = new CGCController(i);
        unk30[i]->setUnk08(&unk40[i]);
        unk30[i]->setUnk0C(&unk70[i]);
    }
}

void CControllerManager::_08(void) {
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk04); i++) {
        delete unk04[i];
    }
    delete unk14;
    MEMDestroyExpHeap(unk18);
    delete[] unk2C;
}

void CControllerManager::_14(void) {
    WPADRegisterAllocator(CControllerManager::fn_801D5950, CControllerManager::fn_801D59B0);
    KPADInit();
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk04); i++) {
        unk04[i]->_0C();
    }
    PADInit();
    memset(unk40, 0, sizeof(unk40));
    memset(unk70, 0, sizeof(unk70));
    u8 pos = WPADGetSensorBarPosition();
    if (pos == 0) {
        KPADSetSensorHeight(0, -.1f);
        return;
    }
    if (pos == 1) {
        KPADSetSensorHeight(0, .1f);
        return;
    }
}

void CControllerManager::_18(void) {
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk04); i++) {
        unk04[i]->_10();
    }
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk30); i++) {
        unk30[i]->_0C();
        unk70[i] = unk40[i];
    }
    PADRead(unk40);
    u32 reset = 0;
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk40); i++) {
        if (unk40[i].err == PAD_ERR_NO_CONTROLLER) {
            reset |= (PAD_CHAN0_BIT >> i);
        }
    }
    if (reset) {
        PADReset(reset);
    }
}

void CControllerManager::_1C(void) {
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk04); i++) {
        unk04[i]->_14();
    }
    for (int i = 0; i < (s32)ARRAY_LENGTH(unk30); i++) {
        unk30[i]->_10();
    }
}

CController *CControllerManager::fn_801D5FF0(s32 idx) {
    return unk04[idx];
}

CGCController *CControllerManager::fn_801D6000(s32 idx) {
    return unk30[idx];
}

CGCController::~CGCController(void) {

}

bool CNullController::_3C(void) {
    return false;
}

bool CNullController::_38(void) {
    return false;
}

bool CNullController::_34(void) {
    return false;
}

bool CNullController::_30(void) {
    return false;
}

bool CNullController::_2C(void) {
    return false;
}

bool CNullController::_28(void) {
    return false;
}

bool CNullController::_24(void) {
    return false;
}

u8 CNullController::_18(void) {
    return -3;
}

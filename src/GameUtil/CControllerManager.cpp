#include "CControllerManager.hpp"

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
}

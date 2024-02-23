#include "Menu/SceneMenu.hpp"
#include <string.h>
#include "Mem.hpp"
#include "CFileManager.hpp"
#include "MessageManager.hpp"
#include "CLayout.hpp"
#include "SceneManager.hpp"
#include "CanvasManager.hpp"
#include "CLayoutManager.hpp"
#include "CSoundManager.hpp"
#include "Controller.hpp"
#include "CCheckPointManager.hpp"
#include "CTickFlowManager.hpp"
#include "SaveData.hpp"
#include "CGameManager.hpp"

static u8 lbl_80320140;
static u8 lbl_80320141;
static u8 lbl_80320142;
static u8 lbl_80320143;

const struct {
    wchar_t *unk0;
    void *unk4;
    u8 *unk8;
    wchar_t *unkC;
} lbl_801F8460[106];

u8 *lbl_802E5740[9];

CExScene *CSceneMenu::create(u16 arg0) {
    fn_801D369C(arg0);
    CSceneMenu *scene = new CSceneMenu;
    fn_801D3644();
    scene->setUnk0C(arg0);
    return scene;
}

// TODO: move this
extern "C" void fn_80008EFC(void); 

void CSceneMenu::fn_80006FA4(void) {
    fn_80008EFC();
    fn_801D369C(2);
    if (gFileManager->fn_801D42E0(55)) {
        gFileManager->fn_801D3F94(55, "content2/layout/layout_msg.szs", eHeap_MEM2, 32);
    }
    fn_801D3644();

    if (!gFileManager->fn_801D42FC(0)) {
        return;
    }

    fn_801D369C(1);
    gMessageManager->fn_800883F4();
    gMessageManager->fn_8008807C();
    gMessageManager->fn_80088034();
    gMessageManager->fn_80088088();
    fn_801D3644();
}

void CSceneMenu::_10(void) {
    fn_80006FA4();
}

namespace {
class CMenuLayout : public CLayout {
public:

    CMenuLayout() {
        setUnk0C(0);
    }


    virtual ~CMenuLayout();
    virtual void _10(void);
    virtual void _14(void);
    virtual void _20(void);
private:

    u8 pad14[0x10];
};
}

void CSceneMenu::_14(void) {
    gSceneManager->fn_8008B068();
    lbl_80320274 = false;
    memset(unk34, '\0', sizeof(unk34));
    fn_8000818C();
    gMyCanvasManager->fn_8007BE0C();
    gLayoutManager->_20(1);
    gLayoutManager->_24(55, "");
    gLayoutManager->fn_801D6AEC(1);
    gLayoutManager->registerLayout<CMenuLayout>();

    gSoundManager->fn_801E6ECC(1.0f);
    fn_800077A8(lbl_80320143);
    unkB4 = false;
    fn_801D3638(300);
}

// TODO: tickflow
extern const u8 lbl_801F7890[];
extern const u8 lbl_80320FE0[1]; // sdata2
extern const u8 lbl_8026D3F0[];
extern const u8 lbl_8026F248[];
extern const u8 lbl_80273A50[];
extern const u8 lbl_80276C90[];
extern const u8 lbl_80278AF8[];
extern const u8 lbl_8027A4D8[];
extern const u8 lbl_80284530[];
extern const u8 lbl_802BA4BC[];


void CSceneMenu::_28(void) {
    if (unkB4) {
        return;
    }

    CController *controller = gControllerManager->fn_801D5FF0(0);
    CGCController *gcController = gControllerManager->fn_801D6000(0);
    
    // TODO: regswap in unkInputCheck
    if ((controller->getUnk1340() & 0x800) || (gcController->unkInputCheck(0x100))) {
        u8 *tickflow = lbl_801F8460[lbl_80320143].unk8;
        if (tickflow) {
            if (tickflow == lbl_80320FE0) {
                if (lbl_80320142 == 0) {
                    gCheckPointManager->setUnk2FC(0);
                }
                if (lbl_80320142 == 1) {
                    gCheckPointManager->setUnk2FC(1);
                }
                if (lbl_80320142 == 2) {
                    gCheckPointManager->setUnk2FC(2);
                }

                u32 temp = lbl_80320141 * 9 + lbl_80320140;
                if (!lbl_802E5740[temp]) {
                    return;
                }
                gTickFlowManager->fn_801E1E4C();
                gTickFlowManager->fn_801E1CC0(lbl_802E5740[temp]);
                unkB4 = true;
                return;
            }
            if (tickflow == lbl_801F7890) {
                if (gSaveData->fn_80078F4C()->fn_80077DF8() < 5) {
                    gSaveData->fn_80078F4C()->fn_80077C0C(5);
                }
                gTickFlowManager->fn_801E1E4C();
                gTickFlowManager->fn_801E1CC0(lbl_801F8460[lbl_80320143].unk8);
                unkB4 = true;
                return;
            }
            if (
                (tickflow == lbl_8026F248) || (tickflow == lbl_80276C90) || 
                (tickflow == lbl_80278AF8) || (tickflow == lbl_8027A4D8) || 
                (tickflow == lbl_8026D3F0) || (tickflow == lbl_80273A50) || 
                (tickflow == lbl_80284530) || (tickflow == lbl_802BA4BC)) {
                lbl_80320274 = true;
            }
            gTickFlowManager->fn_801E1E4C();
            gTickFlowManager->fn_801E1CC0(lbl_801F8460[lbl_80320143].unk8);
            unkB4 = true;
            return;
        }
        gGameManager->_20(lbl_801F8460[lbl_80320143].unk4, 3);
        return;
    }
    if (((controller->getUnk133C() & 8) || (controller->getUnk1368() & 8)) 
    || ((gcController->unkInputCheck(8) || (gcController->getUnk14() & 8)))) {
        fn_800077A8((lbl_80320143 + 105) % 106);
        return;
    }
    if (((controller->getUnk133C() & 4) || (controller->getUnk1368() & 4)) 
    || ((gcController->unkInputCheck(4) || (gcController->getUnk14() & 4)))) {
        fn_800077A8((lbl_80320143 + 1) % 106);
        return;
    }
    if (((controller->getUnk133C() & 1) || (controller->getUnk1368() & 1)) 
    || ((gcController->unkInputCheck(1) || (gcController->getUnk14() & 1)))) {
        if ((lbl_80320143 - 20) >= 0) {
            fn_800077A8(lbl_80320143 - 20);
            return;
        }
        if (((lbl_80320143 % 20) + 100) >= 106) {
            fn_800077A8(105);
            return;
        }
        fn_800077A8((lbl_80320143 % 20) + 100);
        return;
    }
    if (((controller->getUnk133C() & 2) || (controller->getUnk1368() & 2)) 
    || ((gcController->unkInputCheck(2) || (gcController->getUnk14() & 2)))) {
        if ((lbl_80320143 + 20) < 106) {
            fn_800077A8(lbl_80320143 + 20);
            return;
        }
        s32 temp = ((lbl_80320143) / 20);
        s32 temp1 = ((lbl_80320143) % 20);
        if (temp < 5) {
            fn_800077A8(105);
            return;
        }
        fn_800077A8(temp1);
        return;
    }
}

void CSceneMenu::_20(void) {
    gFileManager->fn_801D41CC(55);
    fn_80008A20();
}

extern "C" int swprintf(wchar_t *, unsigned, const wchar_t *, ...); // TODO: move to a proper header
extern "C" wchar_t *wcscat(wchar_t *, const wchar_t *); // TODO: move to a proper header

extern wchar_t lbl_80329980[512];
extern wchar_t lbl_8032A180[16];

void CSceneMenu::fn_800077A8(u8 arg1) {
    lbl_80320143 = arg1;
    s32 temp_r26 = 20;
    s32 tempdiv = (lbl_80320143 / 20);
    if (tempdiv == 5) {
        temp_r26 = 6;
    }

    swprintf(lbl_80329980, sizeof(lbl_80329980), L"");
    wcscat(lbl_80329980, unk34);
    wcscat(lbl_80329980, L"\n");
    for (int i = 0; i < temp_r26; i++, tempdiv++) {
        swprintf(lbl_8032A180, sizeof(lbl_8032A180), L"%03d : ", tempdiv);
        wcscat(lbl_80329980, ((tempdiv * 20) == lbl_80320143) ? L"→" : L" ");
        wcscat(lbl_80329980, lbl_8032A180);
        wcscat(lbl_80329980, lbl_801F8460[tempdiv].unk0);
        wcscat(lbl_80329980, L"\n");
    }
    // TODO: keep going
}

void CMenuLayout::_14(void) {
    CLayout::_14();
}

void CMenuLayout::_10(void) {

}

CMenuLayout::~CMenuLayout(void) {
    _14();
}


void CSceneMenu::_1C(void) {
    CExScene::_1C();
}

void CSceneMenu::_18(void) {
    CExScene::_18();
}

CSceneMenu::~CSceneMenu(void) {

}

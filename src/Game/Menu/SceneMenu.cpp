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

static u8 lbl_80320140;
static u8 lbl_80320141;
static u8 lbl_80320142;
static u8 lbl_80320143;


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

void CSceneMenu::_28(void) {
    if (unkB4) {
        return;
    }

    // TODO: here
}
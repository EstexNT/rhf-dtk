#include "Menu/SceneMenu.hpp"
#include <string.h>
#include "Mem.hpp"
#include "CFileManager.hpp"
#include "MessageManager.hpp"
#include "CLayout.hpp"
#include "SceneManager.hpp"

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
class CMenuLayout : CLayout {
public:
    CMenuLayout() {

    }
};
}

void CSceneMenu::_14(void) {
    gSceneManager->fn_8008B068();
    lbl_80320274 = false;
    memset(unk34, '\0', sizeof(unk34));
    fn_8000818C();
    
}

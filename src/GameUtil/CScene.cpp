#include "CScene.hpp"
#include "Mem.hpp"
#include "CGameManager.hpp"
#include "CFileManager.hpp"

void CScene::fn_801D83BC(void) {
    delete this;
}

void CScene::fn_801D83DC(void) {
    fn_801D369C(unk0C);
    switch (unk08) {
        case 0:
            _10();
            unk08 = 1;
            break;
        case 1:
            if (_24()) {
                _14();
                if (unk04) {
                    _18();
                    unk04 = 0;
                }
                unk08 = 2;
                fn_801D3634();
            }
            break;
        case 2:
            if (gGameManager->_30()) {
                unk08 = 3;
            }
            break;
        case 3:
            _18();
            break;
        case 4:
            if (gGameManager->_2C()) {
                unk08 = 5;
            }
            break;
        case 5:
            _20();
            unk08 = 6;
            break;
    }
    fn_801D3644();
}

void CScene::fn_801D8554(void) {
    if (!((unk08 == 2) || (unk08 == 3) || (unk08 == 4))) {
        return;
    }
    _1C();
}

void CScene::fn_801D8578(void) {
    unk08 = 4;
    gGameManager->_28();
}

bool CScene::_24(void) {
    return gFileManager->fn_801D431C();
}

// TODO: this doesn't belong here.. probably
class class_801D859C {
public:
    virtual void _08(void);
    virtual void _0C(void);
    virtual void _10(void);
    virtual ~class_801D859C(void);
    
    void fn_801D859C(void);
};

void class_801D859C::fn_801D859C(void) {
    delete this;
}

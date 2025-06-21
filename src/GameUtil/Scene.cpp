#include "Scene.hpp"

#include "GameManager.hpp"
#include "FileManager.hpp"

#include "FaderFlash.hpp"

void CScene::fn_801D83BC(void) {
    delete this;
}

void CScene::fn_801D83DC(void) {
    fn_801D369C(mHeapId);
    switch (mState) {
        case eState_Unprepared:
            _10();
            mState = eState_Preparing;
            break;
        case eState_Preparing:
            if (_24()) {
                _14();
                if (unk04) {
                    _18();
                    unk04 = 0;
                }
                mState = eState_Prepared;
                fn_801D3634();
            }
            break;
        case eState_Prepared:
            if (gGameManager->_30()) {
                mState = eState_3;
            }
            break;
        case eState_3:
            _18();
            break;
        case eState_4:
            if (gGameManager->_2C()) {
                mState = eState_5;
            }
            break;
        case eState_5:
            _20();
            mState = eState_Finished;
            break;
    }
    fn_801D3644();
}

void CScene::fn_801D8554(void) {
    if (!((mState == eState_Prepared) || (mState == eState_3) || (mState == eState_4))) {
        return;
    }
    _1C();
}

void CScene::fn_801D8578(void) {
    mState = eState_4;
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

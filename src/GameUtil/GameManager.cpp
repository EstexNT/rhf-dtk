#include "GameManager.hpp"

#include "Mem.hpp"

#include "FileManager.hpp"
#include "TickFlowManager.hpp"
#include "InputCheckManager.hpp"
#include "CheckPointManager.hpp"
#include "SoundManager.hpp"
#include "GraphicManager.hpp"

#include "VarParam.hpp"

#include "Controller.hpp"

#include <revolution/OS.h>
#include <revolution/DVD.h>

#include "DiscMessages.hpp"

#include <revolution/VI.h>

#include <revolution/GX.h>

#include <nw4r/ut.h>

#include <nw4r/db/assert.h>

CGameManager::DvdMessageData CGameManager::sDvdMessageData;

bool CGameManager::sIsPowerOff;
bool CGameManager::sIsReset;

CGameManager::CGameManager(void) {}

CGameManager::~CGameManager(void) {
    _08();
}

void CGameManager::_10(void) {}

void CGameManager::_08(void) {}

extern u8 lbl_80316560[0x8180]; // DVD message font data.

void CGameManager::_14(void) {
    mCurrentScene = NULL;
    mNextSceneCreateFunc = NULL;
    mNextTickFlowCode = NULL;

    sDvdMessageData.font.SetResource(lbl_80316560);
}

void CGameManager::_18(void) {}

void CGameManager::_1C(CScene::CreateFn initSceneCreateFn, CFaderFlash *fader, u16 initSceneHeapId) {
    MEMGetTotalFreeSizeForExpHeap(lbl_80320F80);
    MEMGetTotalFreeSizeForExpHeap(lbl_80320F84);

    mCurrentScene = initSceneCreateFn(initSceneHeapId);
    mFader = fader;

    while (TRUE) {
        if (mCurrentScene->getState() == CScene::eState_3) {
            gControllerManager->_18();
        }

        gFileManager->fn_801D49D4();
        gFileManager->fn_801D4544();

        gTickFlowManager->_18();

        gInputCheckManager->fn_801E8A08();

        gCheckPointManager->fn_801EAE20();

        if (mCurrentScene->getState() == CScene::eState_Finished) {
            u16 heapId = mCurrentScene->getHeapId();
            mCurrentScene->fn_801D83BC();

            fn_801D375C(heapId);
            fn_801D3770(heapId);

            mCurrentScene = mNextSceneCreateFunc(mNextSceneHeapId);
        }

        bool wasLoading = mCurrentScene->getState() == CScene::eState_Preparing;

        mCurrentScene->fn_801D83DC();

        mFader->_08();

        gSoundManager->fn_801E4D60();
        
        bool isNowInitialized = mCurrentScene->getState() == CScene::eState_Prepared;

        if (wasLoading && isNowInitialized && mNextTickFlowCode != NULL) {
            gTickFlowManager->fn_801E1CC0(mNextTickFlowCode);
            mNextTickFlowCode = NULL;
        }

        gGraphicManager->fn_801D63B4();

        mCurrentScene->fn_801D8554();

        mFader->_0C();

        mCurrentScene->_08();

        gVarParamManager->fn_801ED2AC();

        gGraphicManager->fn_801D6478();

        if (mCurrentScene->getState() == 3) {
            gControllerManager->_1C();
        }
    }
}

void CGameManager::_20(CScene::CreateFn sceneCreateFn, u16 heapId) {
    mNextSceneCreateFunc = sceneCreateFn;
    mNextSceneHeapId = heapId;
    mCurrentScene->fn_801D8578();
}

void CGameManager::osPowerCallback(void) {
    sIsPowerOff = true;
}
void CGameManager::osResetCallback(void) {
    sIsReset = true;
}

void CGameManager::fn_801D7538(s32 dvdDriveStatus) {
    switch (dvdDriveStatus) {
    case DVD_STATE_NO_DISK:
        sDvdMessageData.messageStr = lbl_80316400;
        break;
    case DVD_STATE_WRONG_DISK:
        sDvdMessageData.messageStr = lbl_8031645C;
        break;
    case DVD_STATE_RETRY:
        sDvdMessageData.messageStr = lbl_803164B8;
        break;
    default:
        break;
    }

    sIsPowerOff = false;
    sIsReset = false;

    OSStateCallback prevResetCallback = OSSetResetCallback(osResetCallback);
    OSStateCallback prevPowerCallback = OSSetPowerCallback(osPowerCallback);

    while (dvdDriveStatus == (s32)DVDGetDriveStatus()) {
        gGraphicManager->fn_801D63B4();

        if (CSoundManager::fn_801E4D4C()) {
            gSoundManager->fn_801E4D60();
        }

        sDvdMessageData.fn_801D77A4();

        if (sIsReset) {
            VISetBlack(TRUE);
            VIFlush();
            VIWaitForRetrace();
            VIWaitForRetrace();
            OSReturnToMenu();
        }
        else if (sIsPowerOff) {
            VISetBlack(TRUE);
            VIFlush();
            VIWaitForRetrace();
            VIWaitForRetrace();
            OSShutdownSystem();
        }

        gGraphicManager->fn_801D6478();
    }

    while (
        (CSoundManager::fn_801E4D4C() && gSoundManager->fn_801E7334()) ||
        gFileManager->fn_801D3D58()
    ) {
        gGraphicManager->fn_801D63B4();

        if (CSoundManager::fn_801E4D4C()) {
            gSoundManager->fn_801E4D60();
        }

        sDvdMessageData.fn_801D77A4();

        if (sIsReset) {
            VISetBlack(TRUE);
            VIFlush();
            VIWaitForRetrace();
            VIWaitForRetrace();
            OSReturnToMenu();
        }
        else if (sIsPowerOff) {
            VISetBlack(TRUE);
            VIFlush();
            VIWaitForRetrace();
            VIWaitForRetrace();
            OSShutdownSystem();
        }

        gGraphicManager->fn_801D6478();
    }

    OSSetResetCallback(prevResetCallback);
    OSSetPowerCallback(prevPowerCallback);
}

CGameManager::DvdMessageData::~DvdMessageData(void) {}

void CGameManager::DvdMessageData::fn_801D77A4() {
    u32 sc[4];
    f32 vp[6];

    GXGetViewportv(vp);
    GXGetScissor(&sc[0], &sc[1], &sc[2], &sc[3]);

    f32 near = 0.0f;
    f32 far = 1.0f;

    f32 top = 0.0f;
    f32 bottom = 456.0f;
    f32 left = 0.0f;
    f32 right = 608.0f;

    Mtx44 projMtx;
    C_MTXOrtho(projMtx, top, bottom, left, right, near, far);
    GXSetProjection(projMtx, GX_ORTHOGRAPHIC);

    Mtx mtx;
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, 0);

    GXSetCurrentMtx(0);

    GXClearVtxDesc();
    GXInvalidateVtxCache();
    GXInvalidateTexAll();

    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumIndStages(0);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_RASC,GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_RASA,GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_TEV_SCALE_0, TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_TEV_SCALE_0, TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetColorUpdate(TRUE);
    GXSetAlphaUpdate(TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetZMode(FALSE, GX_ALWAYS, FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);

    GXSetCullMode(GX_CULL_NONE);
    GXSetClipMode(GX_CLIP_ENABLE);

    GXSetTevColor(GX_TEVREG0, (GXColor){0, 0, 0, 0xFF});

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition2f32(left, top);
    GXColor1u32(0xFFFFFFFF);

    GXPosition2f32(left, bottom);
    GXColor1u32(0xFFFFFFFF);

    GXPosition2f32(right, bottom);
    GXColor1u32(0xFFFFFFFF);

    GXPosition2f32(right, top);
    GXColor1u32(0xFFFFFFFF);

    GXEnd();

    fn_801D7A74();

    GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
    GXSetScissor(sc[0], sc[1], sc[2], sc[3]);
}

void CGameManager::DvdMessageData::fn_801D7A74() {
    nw4r::ut::TextWriterWide textWriter;

    textWriter.SetFont(this->font);
    textWriter.SetCharSpace(2.0f);
    textWriter.SetFontSize(15.0f, 22.5f);
    textWriter.SetTextColor(nw4r::ut::Color::WHITE);

    const wchar_t *string = this->messageStr;

    nw4r::ut::Rect textRect;
    textWriter.CalcStringRect(&textRect, string);

    textWriter.SetupGX();

    f32 cursorX = (608.0f - (textRect.right - textRect.left)) / 2.0f;
    f32 cursorY = (456.0f - (textRect.bottom - textRect.top)) / 2.0f;

    textWriter.SetCursor(cursorX, cursorY);
    textWriter.Print(string);
}

bool CGameManager::_2C(void) {
    return mFader->getUnk04() == 2;
}

void CGameManager::_28(void) {
    mFader->_10();
}

void CGameManager::_24(CFaderFlash *fader) {
    mFader->fn_801D859C();
    mFader = fader;
}

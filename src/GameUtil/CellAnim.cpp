#include "CellAnimManager.hpp"
#include "Mem.hpp"
#include "TickFlowManager.hpp"

CCellAnim::CCellAnim(void) {

}

CCellAnim::~CCellAnim(void) {

}

void CCellAnim::init(u8 id, u16 animID) {
    mID = id;
    mAnimID = animID;
    mPrepAnimCount = 0;
    mTotalFrames = gCellAnimManager->fn_801DBB58(this);
    mEnabled = true;
    mLinear = true;
    mUpdate = false;
    mFrame = 0.0f;
    mSpeed = 1.0f;
    mLooping = false;
    mBackward = false;
    mDestroyAtEnd = false;
    mDisableAtEnd = false;
    mTempoUpdate = false;
    mTempo = 120;
    mPos = nw4r::math::VEC2(0.0f, 0.0f);
    mSize = nw4r::math::VEC2(1.0f, 1.0f);
    mAngle = 0.0f;
    mLayer = 0;
    mTexNumber = -1;
    mFgColorR = 0;
    mFgColorG = 0;
    mFgColorB = 0;
    mBgColorR = 0xff;
    mBgColorG = 0xff;
    mBgColorB = 0xff;
    mOpacity = 0xff;
    setNext(0);
    setPrev(0);
    mBaseCell = 0;
    mBaseExtCellFirst = 0;
    mBaseExtCellNext = 0;
    mBaseExtCell2 = 0;
    mBaseCellDraw = 0;
}

// Returns true if the cellanim needs to be destoryed afterwards
// regswap between totalFrames and nextAnimID (and inside the prep anim for-loop)
bool CCellAnim::update(void) {
    if (mUpdate) {
        if (mFrame < 0.0f) {
            mFrame = 0.0f;
        } else {
            f32 speed;
            if (mTempoUpdate) {
                f32 currTempo = gTickFlowManager->fn_801E2CA8();
                f32 cellTempo = mTempo;
                f32 d = (currTempo - cellTempo);
                if (((-2.0 < d) && (d < 2.0))) {
                    speed = mSpeed;
                } else {
                    speed = (mSpeed * currTempo) / cellTempo;
                }
            } else {
                speed = mSpeed;
            }
            f32 frame;
            if (gTickFlowManager->fn_801E4178()) {
                frame = mFrame + speed;
            } else {
                frame = mFrame + (30.0f / 25.0f) * speed; // (ntsc / pal)
            }
            mFrame = frame;
        }
        u16 totalFrames = mTotalFrames;
        while (mFrame >= totalFrames) {
            // handle overhead frames (only executed when animation has ended)
            if (mPrepAnimCount) {
                // prepared animations
                u16 prevAnimID = mAnimID;
                u16 nextAnimID = mPrepAnimID[0];
                if (mPrepAnimCallback[0]) {
                    mPrepAnimCallback[0](this, prevAnimID, nextAnimID);
                }
                mPrepAnimCount--;
                for (int i = 0; i < mPrepAnimCount; i++) {
                    mPrepAnimID[i + 0] = mPrepAnimID[i + 1];
                    mPrepAnimCallback[i + 0] = mPrepAnimCallback[i + 1];
                }
                mAnimID = nextAnimID;
                mTotalFrames = gCellAnimManager->fn_801DBB58(this);
                mUpdate = true;
                mFrame = -1.0f;
            } else {
                // finised all animations
                if (mLooping) {
                    mFrame -= totalFrames;
                    continue;
                }
                mUpdate = false;
                mFrame = totalFrames;
                if (mDestroyAtEnd) {
                    return true;
                }
                if (mDisableAtEnd) {
                    mEnabled = false;
                }
                break;
            }
        }
    }
    return false;
}

// regswaps, wS/hS weirdness
void CCellAnim::makeMtx(BOOL defMtx, Mtx baseMtx) {
    if (defMtx && mBaseCell) {
        return;
    }
    BrcadAnimationKey *key = gCellAnimManager->fn_801DBC7C(this);
    CellAnimSprite *sprite = gCellAnimManager->fn_801DBD38(this);
    Mtx transMtx;
    Mtx rotMtx;
    Mtx scaleMtx;
    Mtx tempMtx;

    if (defMtx) {
        MTXIdentity(mMtx);
    } else {
        MTXCopy(baseMtx, mMtx);
    }

    if ((mPos.x != 0.0) || (mPos.y != 0.0)) {
        MTXTrans(transMtx, mPos.x, mPos.y, 0.0f);
        MTXConcat(mMtx, transMtx, mMtx);
    }
    if (mAngle != 0.0) {
        MTXRotDeg(rotMtx, 'z', mAngle);
        MTXConcat(mMtx, rotMtx, mMtx);
    }
    if ((mSize.x != 1.0) || (mSize.y != 1.0)) {
        MTXScale(scaleMtx, mSize.x, mSize.y, 1.0f);
        MTXConcat(mMtx, scaleMtx, mMtx);
    }

    if ((key->transform.posX != 0.0) || (key->transform.posY != 0.0)) {
        MTXTrans(transMtx, key->transform.posX, key->transform.posY, 0.0f);
        MTXConcat(mMtx, transMtx, mMtx);
    }
    if (key->transform.angle != 0.0) {
        MTXRotDeg(rotMtx, 'z', key->transform.angle);
        MTXConcat(mMtx, rotMtx, mMtx);
    }
    if ((key->transform.scaleX != 1.0) || (key->transform.scaleY != 1.0)) {
        MTXScale(scaleMtx, key->transform.scaleX, key->transform.scaleY, 1.0f);
        MTXConcat(mMtx, scaleMtx, mMtx);
    }

    if (mBaseExtCellFirst) {
        u16 texWidth = gCellAnimManager->fn_801DBE04(mID); // unused
        u16 texHeight = gCellAnimManager->fn_801DBE14(mID); // unused

        for (int i = 0; i < sprite->partNum; i++) {
            bool haseBaseExt = false;
            for (CCellAnim *cell = mBaseExtCellFirst; cell != 0; cell = cell->mBaseExtCellNext) {
                if (i == cell->mBasePartNum) {
                    haseBaseExt = true;
                    break;
                }
            }
            if (haseBaseExt) {
                CellAnimSpritePart *parts = sprite->parts;
                f32 wS = parts[i].transform.scaleX * parts[i].regionW * 0.5f + parts[i].transform.posX;
                f32 hS = parts[i].transform.scaleY * parts[i].regionH * 0.5f + parts[i].transform.posY;
                if ((wS != 0.0) || (hS != 0.0)) {
                    MTXTrans(transMtx, wS, hS, 0.0f);
                    MTXConcat(mMtx, transMtx, tempMtx);
                } else {
                    MTXCopy(mMtx, tempMtx);
                }
                if (parts[i].transform.angle != 0.0) {
                    MTXRotDeg(rotMtx, 'z', parts[i].transform.angle);
                    MTXConcat(tempMtx, rotMtx, tempMtx);
                }
                if ((parts[i].transform.scaleX != 1.0) || (parts[i].transform.scaleY != 1.0)) {
                    MTXScale(scaleMtx, parts[i].transform.scaleX, parts[i].transform.scaleY, 1.0f);
                    MTXConcat(tempMtx, scaleMtx, tempMtx);
                }
                for (CCellAnim *cell = mBaseExtCellFirst; cell != 0; cell = cell->mBaseExtCellNext) {
                    if (i == cell->mBasePartNum) {
                        makeMtx(FALSE, tempMtx);
                    }
                }
            }
        }
    }
}

void CCellAnim::draw(BOOL forceDraw) {
    // TODO
}

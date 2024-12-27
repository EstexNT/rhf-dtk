#ifndef GAMEUTIL_CCELLANIM_HPP
#define GAMEUTIL_CCELLANIM_HPP

#include <revolution/types.h>
#include <revolution/MTX.h>
#include <nw4r/math/types.h>
#include "List.hpp"


class CCellAnim : public CList {
public:

    typedef void (*CellAnimPrepFn)(CCellAnim *cell, u16 animID, u16 nextAnimID);

    CCellAnim *getNext(void) {
        return static_cast<CCellAnim *>(this->CList::getNext());
    }
    CCellAnim *getPrev(void) {
        return static_cast<CCellAnim *>(this->CList::getPrev());
    }

    CCellAnim(void);
    ~CCellAnim(void);
    void init(u8 id, u16 animID);
    bool update(void);
    void makeMtx(BOOL defMtx, Mtx baseMtx);
    void draw(BOOL forceDraw);
private:

    u8 mID;
    u16 mAnimID;
    u16 mPrepAnimID[8];
    u8 mPrepAnimCount;
    CellAnimPrepFn mPrepAnimCallback[8];
    f32 mFrame;
    s16 mTotalFrames;
    f32 mSpeed;
    u16 mTempo;
    Mtx mMtx;
    nw4r::math::VEC2 mPos;
    nw4r::math::VEC2 mSize;
    f32 mAngle;
    s32 mLayer;
    s32 mTexNumber;
    u8 mFgColorR, mFgColorG, mFgColorB;
    u8 mBgColorR, mBgColorG, mBgColorB;
    u8 mOpacity; // alpha
    bool mEnabled;
    bool mLinear;
    bool mUpdate;
    bool mLooping;
    bool mBackward;
    bool mDestroyAtEnd;
    bool mDisableAtEnd;
    bool mTempoUpdate;
    CCellAnim *mBaseCell;
    CCellAnim *mBaseExtCellFirst;
    CCellAnim *mBaseExtCellNext; // unsure
    CCellAnim *mBaseExtCell2; // unsure
    u16 mBasePartNum;
    bool mBaseCellDraw;
};

#endif
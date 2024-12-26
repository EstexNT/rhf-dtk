#ifndef GAMEUTIL_CLAYOUT_HPP
#define GAMEUTIL_CLAYOUT_HPP

#include <revolution/types.h>
#include <nw4r/lyt/layout.h>
#include <nw4r/lyt/drawInfo.h>
#include "LayoutAnimation.hpp"

class CLayout {
public:

    virtual ~CLayout(void) {

    }
    virtual void _0C(void);
    virtual void _10(void);
    virtual void _14(void);
    virtual void _18(nw4r::lyt::DrawInfo *);
    virtual void _1C(nw4r::lyt::DrawInfo *);
    virtual void _20(void);
    
    CLayout(void);

    void fn_801D9B10(void);

    nw4r::lyt::Layout *getLayout(void) {
        return unk04;
    }
    void buildLayout(const void *buf, nw4r::lyt::ResourceAccessor *resAccessor) {
        getLayout()->Build(buf, resAccessor);
    }
    void setUnk0C(s32 arg0) {
        unk0C = arg0;
    }
    u8 getUnk10(void) {
        return unk10;
    }
    u8 getUnk11(void) {
        return unk11;
    }
private:

    nw4r::lyt::Layout *unk04;
    CLayoutAnimation *unk08;
    s32 unk0C;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    f32 unk14;
    f32 unk18;
};

#endif
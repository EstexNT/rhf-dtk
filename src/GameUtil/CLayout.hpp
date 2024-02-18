#ifndef GAMEUTIL_CLAYOUT_HPP
#define GAMEUTIL_CLAYOUT_HPP

#include <revolution/types.h>
#include <nw4r/lyt/lyt_layout.h>
#include "CLayoutAnimation.hpp"

class CLayout {
public:

    virtual ~CLayout(void) {

    }
    virtual void _0C(void);
    virtual void _10(void);
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void);
    virtual void _20(void);
    
    CLayout(void);

    void setUnk0C(s32 arg0) {
        unk0C = arg0;
    }

    nw4r::lyt::Layout *getLayout(void) {
        return unk04;
    }

private:
    nw4r::lyt::Layout *unk04;
    CLayoutAnimation *unk08;
    s32 unk0C;
    u8 unk10;
    u8 unk11;
};

#endif
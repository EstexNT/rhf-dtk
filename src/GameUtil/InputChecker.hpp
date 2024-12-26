#ifndef GAMEUTIL_CINPUTCHECKER_HPP
#define GAMEUTIL_CINPUTCHECKER_HPP

#include <revolution/types.h>
#include "List.hpp"

class CInputChecker : public CList {
public:

    virtual ~CInputChecker(void);
    virtual void finalInsert(void);
    virtual void finalDestroy(void);
    virtual void _14(void);
    virtual u32 _18(void); 
    virtual u32 _1C(void); // weak
    virtual u32 _20(u8 *, u32, f32);
    virtual u32 _24(u32);
    virtual u32 _28(u32);
    virtual void _2C(void);
    virtual u32 _30(u32);
    // TODO

    u32 fn_801E7E28(u32);
    u32 fn_801E7E70(u32);

    u8 getUnk50(void) {
        return unk50;
    }
    u8 getUnk70(void) {
        return unk70;
    }
    u8 getUnk71(void) {
        return unk71;
    }
    u8 getUnk72(void) {
        return unk72;
    }
    u32 getUnk74(void) {
        return unk74;
    }
    u8 getUnk78(void) {
        return unk78;
    }
    

protected:

    u8 pad0C[0x50-0xc];
    u8 unk50;
    u8 pad51[0x70-0x51];
    u8 unk70;
    u8 unk71;
    u8 unk72;
    s32 unk74;
    u8 unk78;
};

#endif

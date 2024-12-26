#ifndef GAMEUTIL_CSCENE_HPP
#define GAMEUTIL_CSCENE_HPP

#include <revolution/types.h>

class CScene {
public:

    virtual void _08(void);
    virtual ~CScene(void) {
        
    }
    virtual void _10(void) = 0;
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void);
    virtual void _20(void);
    virtual bool _24(void); // fn_801D8594
    virtual void _28(void);

    CScene(void) {
        unk08 = 0;
        unk04 = 1;
    }

    void fn_801D83BC(void);
    void fn_801D83DC(void);
    void fn_801D8554(void);
    void fn_801D8578(void);

    void setUnk0C(u16 arg0) {
        unk0C = arg0;
    }
private:

    u8 unk04;
    s32 unk08;
    u16 unk0C;
    u8 unk0E;
};

#endif
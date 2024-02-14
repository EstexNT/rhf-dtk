#ifndef GAME_EXSCENE_HPP
#define GAME_EXSCENE_HPP

#include <revolution/types.h>
#include "CScene.hpp"

class CExScene : private CScene {
public:

    virtual void _08(void);
    virtual ~CExScene(void) {
        
    }
    virtual void _10(void) = 0;
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void);
    virtual void _20(void);
    virtual bool _24(void);
    virtual void _28(void);

    CExScene(void);

private:

    u32 unk10;
    u32 unk14;
    u32 unk18;
};

#endif
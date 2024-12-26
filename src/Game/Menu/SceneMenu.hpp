#ifndef GAME_MENU_SCENEMENU_HPP
#define GAME_MENU_SCENEMENU_HPP

#include <revolution/types.h>
#include "Layout.hpp"
#include "ExScene.hpp"

class CSceneMenu : public CExScene {
public:

    virtual ~CSceneMenu(void);
    virtual void _10(void);
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void);
    virtual void _20(void);
    virtual void _28(void);

    CSceneMenu(void) {

    }

    void fn_800077A8(u8);

    static CExScene *create(u16 arg0);
    static void fn_80006FA4(void);
private:

    wchar_t unk34[64];
    bool unkB4;
};

#endif
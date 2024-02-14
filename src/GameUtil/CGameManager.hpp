#ifndef GAMEUTIL_CGAMEMANAGER_HPP
#define GAMEUTIL_CGAMEMANAGER_HPP

#include <revolution/types.h>
#include "TSingleton.hpp"

class CGameManager : public TSingleton<CGameManager> {
public:

    virtual void _08(void);
    virtual ~CGameManager(void);
    virtual void _10(void);
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void);
    virtual void _20(void *, u32); // TODO: proper type for the CScene::create function
    virtual void _24(void);
    virtual void _28(void);
    virtual bool _2C(void);
    virtual bool _30(void);
    virtual void _34(u32 *tickflow) { // TODO: proper type for TickFlow
        unk14 = tickflow;
    } 
    
private:
    u8 pad04[0x10];
    u32 *unk14;
};

extern CGameManager *gGameManager;

#endif 
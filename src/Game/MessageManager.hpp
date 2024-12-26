#ifndef GAME_MESSAGEMANAGER_HPP
#define GAME_MESSAGEMANAGER_HPP

#include <revolution/types.h>
#include <nw4r/lyt/pane.h>
#include "Singleton.hpp"

class CMessageManager : public TSingleton<CMessageManager> {
public:

    CMessageManager(void);

    void fn_80088034(void);
    void fn_8008807C(void);
    void fn_80088088(void);
    void fn_800883F4(void);
    void fn_80088474(nw4r::lyt::Pane *);
};

extern CMessageManager *gMessageManager;

#endif
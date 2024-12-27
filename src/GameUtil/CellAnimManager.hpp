#ifndef GAMEUTIL_CCELLANIMMANAGER_HPP
#define GAMEUTIL_CCELLANIMMANAGER_HPP

#include <revolution/types.h>
#include "Singleton.hpp"
#include "CellAnim.hpp"
#include "Brcad.hpp"

class CCellAnimManager : public TSingleton<CCellAnimManager> {
public:
    //TODO
    void fn_801DB568(void *, void *, u32);
    void fn_801DBA98(u32);
    s32 fn_801DBB58(CCellAnim *cell);
    BrcadAnimationKey *fn_801DBC7C(CCellAnim *cell);
    CellAnimSprite *fn_801DBD38(CCellAnim *cell);
    u16 fn_801DBE04(u8 id);
    u16 fn_801DBE14(u8 id);
    void *fn_801DBE7C(u32, u32);
    void fn_801DC068(u32);
};

extern CCellAnimManager *gCellAnimManager;

#endif

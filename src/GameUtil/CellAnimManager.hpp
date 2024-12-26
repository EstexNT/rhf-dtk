#ifndef GAMEUTIL_CCELLANIMMANAGER_HPP
#define GAMEUTIL_CCELLANIMMANAGER_HPP

#include <revolution/types.h>
#include "Singleton.hpp"

class CCellAnimManager : public TSingleton<CCellAnimManager> {
public:
    //TODO
    void fn_801DB568(void *, void *, u32);
    void fn_801DBA98(u32);
    void *fn_801DBE7C(u32, u32);
    void fn_801DC068(u32);
};

extern CCellAnimManager *gCellAnimManager;

#endif

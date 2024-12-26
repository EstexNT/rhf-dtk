#ifndef GAMEUTIL_CSOUNDMANAGER_HPP
#define GAMEUTIL_CSOUNDMANAGER_HPP

#include <revolution/types.h>
#include "Singleton.hpp"

class CSoundManager : public TSingleton<CSoundManager> {
public:

    CSoundManager();

    void fn_801E6ECC(f32);
    void fn_801E4F60(u32, f32 = .0f, void * = 0);
};

extern CSoundManager *gSoundManager;

#endif
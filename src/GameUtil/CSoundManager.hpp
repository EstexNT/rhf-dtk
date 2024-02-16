#ifndef GAMEUTIL_CSOUNDMANAGER_HPP
#define GAMEUTIL_CSOUNDMANAGER_HPP

#include <revolution/types.h>
#include "TSingleton.hpp"

class CSoundManager : public TSingleton<CSoundManager> {
public:

    CSoundManager();

    void fn_801E6ECC(f32);
};

extern CSoundManager *gSoundManager;

#endif
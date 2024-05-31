#ifndef GAME_PROLOGUE_MYLAYOUT_HPP
#define GAME_PROLOGUE_MYLAYOUT_HPP

#include <revolution/types.h>
#include "CLayout.hpp"

namespace Prologue {

class CMyLayout : public CLayout {

public:
    CMyLayout(void) {
        setUnk0C(1);
    }
};

}

#endif

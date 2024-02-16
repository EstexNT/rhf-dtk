#ifndef GAMEUTIL_CLAYOUTANIMATION_HPP
#define GAMEUTIL_CLAYOUTANIMATION_HPP

#include <revolution/types.h>

class CLayoutAnimation {
public:

    CLayoutAnimation(void);
    virtual ~CLayoutAnimation(void);

private:
    u8 pad04[0x1c];
};

#endif
#ifndef GAMEUTIL_SINGLETON_HPP
#define GAMEUTIL_SINGLETON_HPP

#include <revolution/types.h>

template <typename T>
class TSingleton { // this is probably incorrect
public:

    virtual void _08(void) {
        
    }
    virtual ~TSingleton(void) {
        _08();
    }
};

#endif
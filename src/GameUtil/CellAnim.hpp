#ifndef GAMEUTIL_CCELLANIM_HPP
#define GAMEUTIL_CCELLANIM_HPP

#include <revolution/types.h>
#include "List.hpp"

class CCellAnim : public CList {
public:

    CCellAnim *getNext(void) {
        return static_cast<CCellAnim *>(this->CList::getNext());
    }
    CCellAnim *getPrev(void) {
        return static_cast<CCellAnim *>(this->CList::getPrev());
    }

    CCellAnim(void);
    ~CCellAnim(void);
private:


};

#endif
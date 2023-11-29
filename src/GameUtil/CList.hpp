#ifndef GAMEUTIL_CLIST_HPP
#define GAMEUTIL_CLIST_HPP

#include <revolution/types.h>

class CList {
public:
    CList();

    virtual ~CList();
    virtual void finalInsert();
    virtual void finalDestroy();

    void insertBefore(CList *);
    void insertAfter(CList *);
    void removeCurrent(void);
    void removeAll(void);

    CList *mNext;
    CList *mPrev;
};

#endif
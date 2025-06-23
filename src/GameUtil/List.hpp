#ifndef GAMEUTIL_CLIST_HPP
#define GAMEUTIL_CLIST_HPP

#include <revolution/types.h>

class CList {
public:
    virtual ~CList();
    virtual void finalInsert();
    virtual void finalDestroy();

    CList();

    void insertBefore(CList *);
    void insertAfter(CList *);
    void removeCurrent(void);
    void removeAll(void);

    CList *getNext(void) const {
        return mNext;
    }
    void setNext(CList *next) {
        mNext = next;
    }

    CList *getPrev(void) const {
        return mPrev;
    }
    void setPrev(CList *prev) {
        mPrev = prev;
    }

private:
    CList *mNext;
    CList *mPrev;
};

#endif
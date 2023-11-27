class CList {
public:
    virtual void _00() = 0;
    virtual void _04() = 0;

    void fn_801EAAE0(CList *);
    CList *mNext;
    CList *mPrev;
};


void CList::fn_801EAAE0(CList *list) {
    mNext = list;
    mPrev = (list != 0) ? list->mPrev : 0;

    if (mNext) {
        mNext->mPrev = this;
    }
    
    if (mPrev) {
        mPrev->mNext = this;
    }
    _04();
}

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

void CList::finalDestroy() {

}

void CList::finalInsert() {

}


CList::CList() {
    mNext = 0;
    mPrev = 0;
}

CList::~CList() {

}

// Insert the current list before the argument list
void CList::insertBefore(CList *list) {
    mNext = list;
    mPrev = (list != 0) ? list->mPrev : 0;

    if (mNext) {
        mNext->mPrev = this;
    }
    
    if (mPrev) {
        mPrev->mNext = this;
    }
    finalInsert();
}

// Insert the current list after the argument list
void CList::insertAfter(CList *list) {
    mNext = (list != 0) ? list->mNext : 0;
    mPrev = list;

    if (mNext) {
        mNext->mPrev = this;
    }
    
    if (mPrev) {
        mPrev->mNext = this;
    }
    finalInsert();
}

void CList::removeCurrent() {
    if (mNext) {
        mNext->mPrev = mPrev;
    }
    if (mPrev) {
        mPrev->mNext = mNext;
    }

    mNext = 0;
    mPrev = 0;
    finalDestroy();
}

void CList::removeAll() {
    CList *current = this;
    CList *next;

    while (current) {
        next = current->mNext;

        if (next) {
            next->mPrev = current->mPrev;
        }
        if (current->mPrev) {
            current->mPrev->mNext = current->mNext;
        }
        
        current->mNext = 0;
        current->mPrev = 0;
        current->finalDestroy();
        
        current = next;
    }
}

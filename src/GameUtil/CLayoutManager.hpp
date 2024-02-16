#ifndef GAMEUTIL_CLAYOUTMANAGER_HPP
#define GAMEUTIL_CLAYOUTMANAGER_HPP

#include <revolution/types.h>
#include "TSingleton.hpp"
#include "CLayout.hpp"

class CLayoutManager : TSingleton<CLayoutManager> {
public:

    CLayoutManager(void);
    virtual void _08(void);
    virtual ~CLayoutManager(void);
    virtual void _10(void); // init
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void);
    virtual void _20(s32);
    virtual void _24(s32, const char *);
    virtual void _28(void);
    
    void fn_801D6AEC(s32);

    void fn_801D6B2C(CLayout *);

    template <typename T>
    void registerLayout(void) {
        fn_801D6B2C(new T);
    }
};

extern CLayoutManager *gLayoutManager;

#endif
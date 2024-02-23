#ifndef GAMEUTIL_CCHECKPOINTMANAGER_HPP
#define GAMEUTIL_CCHECKPOINTMANAGER_HPP

#include <revolution/types.h>
#include "TSingleton.hpp"

class CCheckPointManager : public TSingleton<CCheckPointManager> {
public:

    virtual void _08(void);
    virtual ~CCheckPointManager(void);
    virtual void _10(void);
    virtual void _14(void);

    CCheckPointManager(void);

    void setUnk2FC(u32 arg1) {
        unk2FC = arg1;
    }
private:

    u8 pad04[0x2f8];
    u32 unk2FC;
};

extern CCheckPointManager *gCheckPointManager;

#endif
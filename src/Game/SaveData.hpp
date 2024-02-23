#ifndef GAME_SAVEDATA_HPP
#define GAME_SAVEDATA_HPP

#include <revolution/types.h>
#include "TSingleton.hpp"

struct SaveDataFile {
    u8 pad00[0x280];

    void fn_80077C0C(s8);
    
    s8 fn_80077DF8(void);
};

class CSaveData : public TSingleton<CSaveData> {
public:

    virtual void _08(void);
    virtual ~CSaveData(void);

    CSaveData();

    SaveDataFile *fn_80078F4C(void);
};

extern CSaveData *gSaveData;

#endif

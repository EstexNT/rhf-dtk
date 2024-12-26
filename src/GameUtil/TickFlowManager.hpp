#ifndef GAMEUTIL_CTICKFLOWMANAGER_HPP
#define GAMEUTIL_CTICKFLOWMANAGER_HPP

#include <revolution/types.h>
#include "Singleton.hpp"

class CTickFlowManager : public TSingleton<CTickFlowManager> {
public:

    virtual void _08(void);
    virtual ~CTickFlowManager(void);
    virtual void _10(void);
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void *, u32);
    

    void fn_801E1E4C(void);
    void fn_801E1CC0(u8 *tickflow, f32 initRest = 0.0f); // TODO: proper type for tickflow
    f32 fn_801E2698();

    u8 getUnk6D(void) {
        return unk6D;
    }
private:

    u8 pad04[0x68];
    u8 unk6C;
    u8 unk6D;
};


extern CTickFlowManager *gTickFlowManager;

#endif
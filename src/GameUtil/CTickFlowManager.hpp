#ifndef GAMEUTIL_CTICKFLOWMANAGER_HPP
#define GAMEUTIL_CTICKFLOWMANAGER_HPP

#include <revolution/types.h>
#include "TSingleton.hpp"

class CTickFlowManager : public TSingleton<CTickFlowManager> {
public:

    virtual void _08(void);
    virtual ~CTickFlowManager(void);

    void fn_801E1E4C(void);
    void fn_801E1CC0(u32 *tickflow, f32 initRest = 0.0f); // TODO: proper type for tickflow
};


extern CTickFlowManager *gTickFlowManager;

#endif
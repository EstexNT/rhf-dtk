#ifndef GAMEUTIL_CGRAPHICMANAGER_HPP
#define GAMEUTIL_CGRAPHICMANAGER_HPP

#include <revolution/types.h>

#include "Singleton.hpp"

#include <revolution/GX.h>

class CGraphicManager : public TSingleton<CGraphicManager> {
public:
    virtual void _08(void);
    virtual ~CGraphicManager(void);
    virtual void _10(void);
    virtual void _14(GXRenderModeObj *renderMode, GXColor *clearColor, u32 clearZ);

    CGraphicManager(void);

    void fn_801D63B4(void);
    void fn_801D6478(void);
    void fn_801D6514(GXRenderModeObj *renderMode);
    void fn_801D6680(void);

private:
    static GXRenderModeObj sRenderModeObj;

    bool mScreenBlack;

    void *mFifoMem;
    GXFifoObj *mFifoObj;

    GXRenderModeObj *mRenderMode;

    u32 mFrameBufferSize;
    void *mFrameBuffers[2];
    void *mCurrentFrameBuf;
};

extern CGraphicManager *gGraphicManager;

#endif

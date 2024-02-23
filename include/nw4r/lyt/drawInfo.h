#ifndef NW4R_LYT_DRAWINFO_H
#define NW4R_LYT_DRAWINFO_H

#include <revolution/types.h>
#include <nw4r/math/types.h>
#include <nw4r/ut/Rect.h>

namespace nw4r {
namespace lyt {

class DrawInfo {
public:

    DrawInfo();
    virtual ~DrawInfo();

    void SetLocationAdjust(u8 bEnable) {
        mFlag.locationAdjust = bEnable;
    }

    void SetLocationAdjustScale(const math::VEC2 &scale) {
        mLocationAdjustScale = scale;
    }


protected:
    math::MTX34 mViewMtx;
    ut::Rect mViewRect;
    math::VEC2 mLocationAdjustScale;
    f32 mGlobalAlpha;
    struct {
        u8 mulViewDraw:1;
        u8 influencedAlpha:1;
        u8 locationAdjust:1;
        u8 invisiblePaneCalculateMtx:1;
        u8 debugDrawMode:1;
    } mFlag;

};

}
}

#endif

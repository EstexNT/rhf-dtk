#include "Pseudo3D.hpp"

CPseudo3D::CPseudo3D(void) {}
CPseudo3D::~CPseudo3D(void) {}

void CPseudo3D::fn_80072A14(f32 centerX, f32 centerY, f32 scale, f32 focX, f32 focY, f32 camZ) {
    mCenterX = centerX;
    mScale = scale;
    mCenterY = centerY;

    mFarZ = camZ / scale;

    f64 perspectiveScale = 1.0 - mFarZ;

    mFarX = (centerX - focX) / perspectiveScale;
    mFarY = (centerY - focY) / perspectiveScale;
}

void CPseudo3D::fn_80072A54(f32 x, f32 y, f32 z, f32 *xOut, f32 *yOut, f32 *scaleOut) {
    f32 perspectiveScale = mFarZ / ((1.0 - mFarZ) * z + mFarZ);

    *xOut = (perspectiveScale * (mFarX + x) + mCenterX) - mFarX;
    *yOut = (perspectiveScale * (mFarY + y) + mCenterY) - mFarY;
    *scaleOut = perspectiveScale * mScale;
}

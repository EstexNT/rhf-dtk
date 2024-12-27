#ifndef RVL_SDK_MTX_MTX_H
#define RVL_SDK_MTX_MTX_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    f32 x, y, z;
} Vec;

typedef struct {
    s16 x, y, z;
} S16Vec;

typedef struct {
    f32 x, y, z, w;
} Quaternion;

typedef f32 Mtx[3][4];
typedef f32 Mtx44[4][4];

#define MTXDegToRad(a) ((a) * 0.01745329252f)
#define MTXRadToDeg(a) ((a) * 57.29577951f)

void MTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);

#ifdef DEBUG
#define VECSquareMag C_VECSquareMag
#define VECNormalize C_VECNormalize
#define VECAdd C_VECAdd
#define VECDotProduct C_VECDotProduct
#define VECSquareDistance C_VECSquareDistance
#define VECCrossProduct C_VECCrossProduct
#define MTXMultVec C_MTXMultVec
#define MTXMultVecArray C_MTXMultVecArray
#define MTXCopy C_MTXCopy
#define MTXConcat C_MTXConcat
#define MTXInverse C_MTXInverse
#define MTXTranspose C_MTXTranspose
#define MTXIdentity C_MTXIdentity
#define MTXScale C_MTXScale
#define MTXRotRad C_MTXRotRad
#define MTXTrans C_MTXTrans
#else
#define VECSquareMag PSVECSquareMag
#define VECNormalize PSVECNormalize
#define VECAdd PSVECAdd
#define VECDotProduct PSVECDotProduct
#define VECSquareDistance PSVECSquareDistance
#define VECCrossProduct PSVECCrossProduct
#define MTXMultVec PSMTXMultVec
#define MTXMultVecArray PSMTXMultVecArray
#define MTXCopy PSMTXCopy
#define MTXConcat PSMTXConcat
#define MTXInverse PSMTXInverse
#define MTXTranspose PSMTXTranspose
#define MTXIdentity PSMTXIdentity
#define MTXScale PSMTXScale
#define MTXRotRad PSMTXRotRad
#define MTXTrans PSMTXTrans
#endif

#define MTXRotDeg(m, axis, deg) \
    MTXRotRad(m, axis, MTXDegToRad(deg))


void MTXRotRad(Mtx m, char axis, f32 rad);
void MTXRotTrig(Mtx m, char axis, f32 sinA, f32 cosA);
void MTXRotAxisRad(Mtx m, Vec *axis, f32 rad);
void MTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void MTXTransApply(Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void MTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void MTXScaleApply(Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);
void MTXQuat(Mtx m, Quaternion *q);
void MTXReflect(Mtx m, Vec *p, Vec *n);
void MTXLookAt(Mtx m, Vec *camPos, Vec *camUp, Vec *target);
void MTXLightFrustum(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void MTXLightPerspective(Mtx m, f32 fovY, f32 aspect, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void MTXLightOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS, f32 transT);

void C_MTXIdentity(Mtx m);
void C_MTXCopy(Mtx src, Mtx dst);
void C_MTXConcat(Mtx a, Mtx b, Mtx ab);
void C_MTXTranspose(Mtx src, Mtx xPose);
u32 C_MTXInverse(Mtx src, Mtx inv);
u32 C_MTXInvXpose(Mtx src, Mtx invX);

void PSMTXIdentity(Mtx m);
void PSMTXCopy(Mtx src, Mtx dst);
void PSMTXConcat(Mtx mA, Mtx mB, Mtx mAB);
void PSMTXTranspose(Mtx src, Mtx xPose);
u32 PSMTXInverse(Mtx src, Mtx inv);
u32 PSMTXInvXpose(Mtx src, Mtx invX);


void MTXMultVecSR(Mtx44 m, Vec *src, Vec *dst);
void MTXMultVecArraySR(Mtx44 m, Vec *srcBase, Vec *dstBase, u32 count); 

void C_MTXMultVec(Mtx44 m, Vec *src, Vec *dst);
void C_MTXMultVecArray(Mtx m, Vec *srcBase, Vec *dstBase, u32 count);

void PSMTXMultVec(Mtx44 m, Vec *src, Vec *dst);
void PSMTXMultVecArray(Mtx m, Vec *srcBase, Vec *dstBase, u32 count);


f32 VECMag(Vec *v);
void VECHalfAngle(Vec *a, Vec *b, Vec *half);
void VECReflect(Vec *src, Vec *normal, Vec *dst);
f32 VECDistance(Vec *a, Vec *b);

void C_VECAdd(Vec *a, Vec *b, Vec *c);
void C_VECSubtract(Vec *a, Vec *b, Vec *c);
void C_VECScale(Vec *src, Vec *dst, f32 scale);
void C_VECNormalize(Vec *src, Vec *unit);
f32 C_VECSquareMag(Vec *v);
f32 C_VECDotProduct(Vec *a, Vec *b);
void C_VECCrossProduct(Vec *a, Vec *b, Vec *axb);
f32 C_VECSquareDistance(Vec *a, Vec *b);

void PSVECAdd(Vec *a, Vec *b, Vec *c); 
void PSVECSubtract(Vec *a, Vec *b, Vec *c);
void PSVECScale(Vec *src, Vec *dst, f32 scale);
void PSVECNormalize(Vec *vec1, Vec *dst);
f32 PSVECSquareMag(Vec *vec1);
f32 PSVECDotProduct(Vec *vec1, Vec *vec2);
void PSVECCrossProduct(Vec *vec1, Vec *vec2, Vec *dst);
f32 PSVECSquareDistance(Vec *vec1, Vec *vec2);


#ifdef __cplusplus
}
#endif
#endif

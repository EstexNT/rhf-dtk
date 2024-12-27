#ifndef GAMEUTIL_BRCAD_HPP
#define GAMEUTIL_BRCAD_HPP

#include <revolution/types.h>

struct BrcadTransform {
    s16 posX, posY;
    f32 scaleX, scaleY;
    f32 angle;
};

struct BrcadAnimationKey {
    u16 spriteIndex;
    u16 holdFrames;
    BrcadTransform transform;
    u8 opacity;
};

struct CellAnimSpritePart {
    u16 regionX, regionY;
    u16 regionW, regionH;
    u16 texNumber;
    BrcadTransform transform;
    bool flipX, flipY;
    u8 opacity;
};

struct CellAnimSprite {
    u16 partNum;
    CellAnimSpritePart *parts;
};

#endif

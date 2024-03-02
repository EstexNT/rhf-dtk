#ifndef NW4R_LYT_TYPES_H
#define NW4R_LYT_TYPES_H

#include <revolution/types.h>
#include <nw4r/ut/LinkList.h>
#include <nw4r/lyt/animation.h>

namespace nw4r {
namespace lyt {

struct Size {
    f32 width;
    f32 height;
};

class AnimationLink {
public:

    ut::LinkListNode mLink;
private:

    AnimTransform *mAnimTrans;
    u16 mIdx;
    bool mbDisable;
};

namespace detail {

template <typename T>
inline void SetBit(T *pBits, int pos, bool val) {
    const T mask = T(~(1 << pos));
    *pBits &= mask;
    *pBits |= (val ? 1 : 0) << pos;
}

template <typename T>
inline bool TestBit(T bits, int pos) {
    const T mask = T(1 << pos);
    return 0 != (bits & mask);
}
}

}
}

#endif
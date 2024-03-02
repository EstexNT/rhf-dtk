#ifndef NW4R_LYT_ANIMATION_H
#define NW4R_LYT_ANIMATION_H

#include <revolution/types.h>
#include <nw4r/ut/LinkList.h>
namespace nw4r {
namespace lyt {

namespace res {
struct AnimationBlock;
}

class AnimTransform {
public:

    AnimTransform();
    virtual ~AnimTransform();

    ut::LinkListNode mLink;

protected:

    res::AnimationBlock *mpRes;
    f32 mFrame;
};

}
}

#endif

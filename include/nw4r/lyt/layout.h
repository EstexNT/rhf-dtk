#ifndef NW4R_LYT_LAYOUT_H
#define NW4R_LYT_LAYOUT_H

#include <revolution/types.h>
#include <revolution/MEM.h>
#include <nw4r/ut/LinkList.h>
#include <nw4r/ut/Rect.h>
#include <nw4r/lyt/animation.h>
#include <nw4r/lyt/pane.h>
#include <nw4r/lyt/group.h>
#include <nw4r/lyt/arcResourceAccessor.h>

namespace nw4r {
namespace lyt {

class Layout {
public:

    static MEMAllocator *mspAllocator;

    Layout();
    virtual ~Layout();
    virtual bool Build(const void *lytResBuf, ResourceAccessor *pResAcsr);

    ut::Rect GetLayoutRect() const;
    Pane *GetRootPane() {
        return mpRootPane;
    }

protected:

    ut::LinkList<AnimTransform, offsetof(AnimTransform, mLink)> mAnimTransList;
    Pane *mpRootPane;
    GroupContainer *mpGroupContainer;
    Size mLayoutSize;
};

}
}

#endif

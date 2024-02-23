#ifndef NW4R_LYT_LAYOUT_H
#define NW4R_LYT_LAYOUT_H

#include <revolution/types.h>
#include <revolution/MEM.h>
#include <nw4r/ut/Rect.h>

namespace nw4r {
namespace lyt {

class Layout {
public:

    static MEMAllocator *mspAllocator;

    Layout(void);

    ut::Rect GetLayoutRect(void) const;
private:

    u8 pad00[0x20];
};

//MEMAllocator *Layout::mspAllocator;

}
}

#endif

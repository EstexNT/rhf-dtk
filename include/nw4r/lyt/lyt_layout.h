#ifndef NW4R_LYT_LYT_LAYOUT_H
#define NW4R_LYT_LYT_LAYOUT_H

#include <revolution/types.h>
#include <nw4r/ut/rect.h>

namespace nw4r {
namespace lyt {

class Layout {
public:

    Layout(void);

    ut::Rect GetLayoutRect(void) const;
private:

    u8 pad00[0x20];
};

}
}

#endif
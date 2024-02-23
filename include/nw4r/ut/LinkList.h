#ifndef NW4R_UT_LINK_LIST
#define NW4R_UT_LINK_LIST

#include <revolution/types.h>
#include <nw4r/ut/inlines.h>

namespace nw4r {
namespace ut {

class LinkListNode : private NonCopyable {
public:
    LinkListNode() : mNext(0), mPrev(0) {

    }

private:

    LinkListNode *mNext;
    LinkListNode *mPrev;
};

}
}

#endif

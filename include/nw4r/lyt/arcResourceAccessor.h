#ifndef NW4R_LYT_ARCRESOURCEACCESSOR_H
#define NW4R_LYT_ARCRESOURCEACCESSOR_H

#include <revolution/types.h>
#include <revolution/ARC.h>
#include <nw4r/ut/LinkList.h>
#include <nw4r/lyt/resourceAccessor.h>
#include <nw4r/ut/Font.h>

namespace nw4r {
namespace lyt {

class FontRefLink {
public:

    FontRefLink();
    ~FontRefLink() {}
    void Set(const char *name, ut::Font *pFont);

    ut::LinkListNode mLink;

protected:

    char mFontName[128];
    ut::Font *mpFont;
};

class ArcResourceLink {
public:

    ArcResourceLink(); // TODO: this should be weak
    ~ArcResourceLink(); // TODO: the destructor should be auto-gen'd
    bool Set(void *archiveStart, const char *resourceRootDirectory);

    ut::LinkListNode mLink;

protected:

    ARCHandle mArcHandle;
    char mResRootDir[128];
};

class MultiArcResourceAccessor : public ResourceAccessor {
public:

    MultiArcResourceAccessor();
    virtual ~MultiArcResourceAccessor();
    virtual void *GetResource(u32, const char *, u32 *);
    virtual void *GetFont(const char *);

    void RegistFont(FontRefLink *pLink);
    void UnregistFont(FontRefLink *pLink);
    void Attach(ArcResourceLink *);
    void DetachAll();

private:
    u8 pad04[0x18];
};

}
}

#endif

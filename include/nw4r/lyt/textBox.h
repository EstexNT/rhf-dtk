#ifndef NW4R_LYT_TEXTBOX_H
#define NW4R_LYT_TEXTBOX_H

#include <revolution/types.h>
#include <nw4r/lyt/pane.h>

namespace nw4r {
namespace lyt {

class TextBox : public Pane {
public:

    NW4R_UT_RUNTIME_TYPEINFO;

    TextBox();

    virtual ~TextBox();
    virtual void AllocStringBuffer(u16 minLen);
    virtual void FreeStringBuffer();
    virtual u16 SetString(const wchar_t *str, u16 dstIdx = 0);
    virtual u16 SetString(const wchar_t *str, u16 dstIdx, u16 strLen);
    virtual const ut::Color GetVtxColor(u32 idx) const;
    virtual void SetVtxColor(u32 idx, ut::Color value);
    virtual u8 GetVtxColorElement(u32 idx) const;
    virtual void SetVtxColorElement(u32 idx, u8 value);
    virtual void DrawSelf(const DrawInfo &drawInfo);

protected:

    virtual void LoadMtx(const DrawInfo &drawInfo);
};

}
}

#endif

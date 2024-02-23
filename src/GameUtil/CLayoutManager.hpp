#ifndef GAMEUTIL_CLAYOUTMANAGER_HPP
#define GAMEUTIL_CLAYOUTMANAGER_HPP

#include <revolution/types.h>
#include <revolution/MEM.h>
#include <nw4r/lyt/arcResourceAccessor.h>
#include <nw4r/lyt/drawInfo.h>
#include <nw4r/ut/ResFont.h>
#include <nw4r/ut/ArchiveFont.h>
#include "TSingleton.hpp"
#include "CLayout.hpp"

class CLayoutManager_sub { // CFontInfo
public:

    u8 unk00;
    nw4r::lyt::FontRefLink *unk04;
    nw4r::ut::Font *unk08;
    u8 *unk0C;
};

class CLayoutManager : public TSingleton<CLayoutManager> {
public:

    CLayoutManager(void);
    virtual void _08(void);
    virtual ~CLayoutManager(void);
    virtual void _10(void); // init
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void);
    virtual void _20(s32);
    virtual void _24(s32, const char *);
    virtual void _28(void);
    
    void fn_801D6AEC(u8);
    void fn_801D6B2C(CLayout *);
    void fn_801D6BB0(void);
    CLayout *fn_801D6C50(u8);
    void fn_801D6D78(void);
    void fn_801D6DAC(u8);
    bool fn_801D6E2C(void *, const char *);
    void fn_801D705C(void);
    void fn_801D717C(f32, f32);
    f32 fn_801D7188(void);
    f32 fn_801D7190(void);
    void fn_801D7198(s32);


    template <typename T>
    void registerLayout(void) {
        fn_801D6B2C(new T);
    }
private:

    u8 *unk04;
    MEMiHeapHead *unk08;
    MEMAllocator unk0C;
    u8 unk1C;
    u8 *unk20;
    MEMiHeapHead *unk24;
    MEMAllocator unk28;
    nw4r::lyt::MultiArcResourceAccessor *unk38;
    nw4r::lyt::ArcResourceLink *unk3C;
    u8 unk40;
    u8 unk41;
    CLayoutManager_sub **unk44;
    u8 unk48;
    u8 unk49;
    nw4r::lyt::DrawInfo *unk4C;
    u8 unk50;
    u8 unk51;
    CLayout **unk54;
    f32 unk58;
    f32 unk5C;
};

extern CLayoutManager *gLayoutManager;

#endif
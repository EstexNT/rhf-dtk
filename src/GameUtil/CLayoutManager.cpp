#include <revolution/GX.h>
#include <revolution/SC.h>
#include <nw4r/lyt/init.h>
#include <nw4r/lyt/arcResourceAccessor.h>
#include "Mem.hpp"
#include "CLayoutManager.hpp"
#include "CFileManager.hpp"

// TODO: nw4r::lyt::Layout::mspAllocator is being put here
// will have to decomp nw4r/lyt/lyt_Pane.cpp since it belongs there

CLayoutManager::CLayoutManager(void) {

}

CLayoutManager::~CLayoutManager(void) {
    _08();
}

void CLayoutManager::_10(void) {
    nw4r::lyt::LytInit();

    unk04 = new (eHeap_MEM2, 32) u8[0x100000];
    unk08 = MEMCreateExpHeap(unk04, 0x100000);
    MEMInitAllocatorForExpHeap(&unk0C, unk08, 4);
    nw4r::lyt::Layout::mspAllocator = &unk0C;
    unk1C = 0;
    unk38 = new nw4r::lyt::MultiArcResourceAccessor;
    unk4C = new nw4r::lyt::DrawInfo;
    if (SCGetAspectRatio() == SC_ASPECT_STD) {
        unk4C->SetLocationAdjust(false);
    } else { // SC_ASPECT_WIDE
        unk4C->SetLocationAdjust(true);
        unk4C->SetLocationAdjustScale(nw4r::math::VEC2(0.7307692f, 1.0f));
    }
    unk54 = 0;
    unk44 = 0;
}

void CLayoutManager::_08(void) {
    fn_801D705C();
    MEMDestroyExpHeap(unk08);
    delete unk38;
    delete[] unk04;
}

void CLayoutManager::_14(void) {
    unk50 = 0;
    unk51 = 0;
    unk58 = 1.0f;
    unk5C = 1.0f;
}

void CLayoutManager::_20(s32 arg1) {
    unk3C = new nw4r::lyt::ArcResourceLink[arg1];
    unk40 = arg1;
    unk41 = 0;
}


// snip: goto Layout_ArcResourceLink.cpp

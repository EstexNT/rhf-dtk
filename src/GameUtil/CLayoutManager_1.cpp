#include <revolution/GX.h>
#include <revolution/SC.h>
#include <nw4r/lyt/init.h>
#include <nw4r/lyt/arcResourceAccessor.h>
#include "Mem.hpp"
#include "CLayoutManager.hpp"
#include "CFileManager.hpp"


const char lbl_80329968[] = "\0";

// yes the destructor is -O4 
// no I don't know how that even happened
nw4r::lyt::ArcResourceLink::~ArcResourceLink() {
    
}

void CLayoutManager::_24(s32 arg1, const char *arg2) {
    unk3C[unk41].Set(gFileManager->fn_801D42CC(arg1), arg2);
    unk38->Attach(&unk3C[unk41]);
    unk41++;
}

void CLayoutManager::_28(void) {
    unk38->DetachAll();
    if (unk3C) {
        delete[] unk3C;
        unk3C = 0;
    }
    unk40 = 0;
    unk41 = 0;
    if (unk1C) {
        unk1C = 0;
        MEMDestroyExpHeap(unk24);
        delete[] unk20;
        nw4r::lyt::Layout::mspAllocator = &unk0C;
    }
}

void CLayoutManager::fn_801D6AEC(u8 arg1) {
    unk51 = 0;
    unk50 = arg1;
    unk54 = new CLayout *[arg1];
}

void CLayoutManager::fn_801D6B2C(CLayout *arg1) {
    unk54[unk51] = arg1;
    unk54[unk51]->_0C();
    unk54[unk51]->_10();
    unk51++;
}

void CLayoutManager::fn_801D6BB0(void) {
    for (int i = 0; i < unk51; i++) {
        delete unk54[i];
    }
    if (unk54) {
        delete[] unk54;
        unk54 = 0;
    }
    unk50 = 0;
    unk51 = 0;
}

CLayout *CLayoutManager::fn_801D6C50(u8 arg1) {
    return unk54[arg1];
}

void CLayoutManager::_18(void) {
    for (int i = 0; i < unk51; i++) {
        if (unk54[i]->getUnk10()) {
            unk54[i]->_18(unk4C);
        }
    }
}

void CLayoutManager::_1C(void) {
    fn_801D6D78();
    for (int i = 0; i < unk51; i++) {
        if (unk54[i]->getUnk11()) {
            unk54[i]->_1C(unk4C);
        }
    }
}

void CLayoutManager::fn_801D6D78(void) {
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(FALSE, GX_NEVER, FALSE);
}

void CLayoutManager::fn_801D6DAC(u8 arg1) {
    unk49 = 0;
    unk48 = arg1;
    unk44 = new CLayoutManager_sub *[arg1];
    for (int i = 0; i < unk48; i++) {
        unk44[i] = new CLayoutManager_sub;
    }
}

#define AS_RSFNT(a) ((nw4r::ut::ResFont *)(a))
#define AS_ARCFNT(a) ((nw4r::ut::ArchiveFont *)(a))
bool CLayoutManager::fn_801D6E2C(void *arg1, const char *arg2) {
    if (strstr(arg2, ".brfnt")) {
        unk44[unk49]->unk00 = 0;
    } else if (strstr(arg2, ".brfna")) {
        unk44[unk49]->unk00 = 1;
    }
    
    switch (unk44[unk49]->unk00) {
        case 0:
            unk44[unk49]->unk08 = new nw4r::ut::ResFont;
            AS_RSFNT(unk44[unk49]->unk08)->SetResource(arg1);
            break;
        case 1:
            u32 tempsize = nw4r::ut::ArchiveFont::GetRequireBufferSize(arg1, lbl_80329968);
            unk44[unk49]->unk0C = new (eHeap_MEM2, 32) u8[tempsize];
            unk44[unk49]->unk08 = new nw4r::ut::ArchiveFont;
            AS_ARCFNT(unk44[unk49]->unk08)->Construct(unk44[unk49]->unk0C, tempsize, arg1, lbl_80329968);
            break;
    }
    bool ret = unk44[unk49]->unk00 == 1;
    unk44[unk49]->unk04 = new nw4r::lyt::FontRefLink;
    unk44[unk49]->unk04->Set(arg2, unk44[unk49]->unk08);
    unk38->RegistFont(unk44[unk49]->unk04);
    unk49++;
    return ret;
    
}

void CLayoutManager::fn_801D705C(void) {
    for (int i = 0; i < unk49; i++) {
        unk38->UnregistFont(unk44[i]->unk04);
        switch (unk44[i]->unk00) {
            case 0:
                AS_RSFNT(unk44[i]->unk08)->RemoveResource();
                break;
            case 1:
                AS_ARCFNT(unk44[i]->unk08)->Destroy();
                break;
        }
        delete unk44[i]->unk04;
        delete unk44[i]->unk08;
        delete[] unk44[i]->unk0C;
        delete unk44[i];
    }
    if (unk44) {
        delete[] unk44;
        unk44 = 0;
    }
    unk48 = 0;
    unk49 = 0;
}
#undef AS_RSFNT
#undef AS_ARCFNT

void CLayoutManager::fn_801D717C(f32 arg1, f32 arg2) {
    unk58 = arg1;
    unk5C = arg2;
}

f32 CLayoutManager::fn_801D7188(void) {
    return unk58;
}

f32 CLayoutManager::fn_801D7190(void) {
    return unk5C;
}

void CLayoutManager::fn_801D7198(s32 arg1) {
    unk1C = 1;
    unk20 = new (eHeap_MEM2, 32) u8[arg1];
    unk24 = MEMCreateExpHeap(unk20, arg1);
    MEMInitAllocatorForExpHeap(&unk28, unk24, 4);
    nw4r::lyt::Layout::mspAllocator = &unk28;
}

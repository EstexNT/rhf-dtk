#ifndef NW4R_UT_RUNTIME_TYPEINFO_H
#define NW4R_UT_RUNTIME_TYPEINFO_H

#include <revolution/types.h>
namespace nw4r {
namespace ut {

#define NW4R_UT_RUNTIME_TYPEINFO \
    virtual const nw4r::ut::detail::RuntimeTypeInfo *GetRuntimeTypeInfo() const { return &typeInfo; } \
    static const nw4r::ut::detail::RuntimeTypeInfo typeInfo

namespace detail {

struct RuntimeTypeInfo {
    const RuntimeTypeInfo *mParentTypeInfo;

    RuntimeTypeInfo(const RuntimeTypeInfo *parent) : mParentTypeInfo(parent) {

    }
};

}

}
}

#endif

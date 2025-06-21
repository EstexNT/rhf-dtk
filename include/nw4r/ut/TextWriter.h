#ifndef NW4R_UT_TEXT_WRITER_H
#define NW4R_UT_TEXT_WRITER_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut/TextWriterBase.h>

namespace nw4r {
namespace ut {

typedef TextWriterBase<char> TextWriter;

typedef TextWriterBase<wchar_t> TextWriterWide;

} // namespace ut
} // namespace nw4r

#endif
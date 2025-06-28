#pragma once

namespace nstd {

using size_t = decltype(sizeof(0));
using ptrdiff_t = decltype(static_cast<int *>(0) - static_cast<int *>(0));
using nullptr_t = decltype(nullptr);

}  // namespace nstd

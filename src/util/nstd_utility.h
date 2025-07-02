#pragma once

#include <util/nstd_type_traits.h>

namespace nstd {

template<typename Ty>
constexpr Ty &&forward(remove_reference_t<Ty> &x) noexcept {
	return static_cast<Ty &&>(x);
}

template<typename Ty>
constexpr Ty &&forward(remove_reference_t<Ty> &&x) noexcept {
	// static_assert(, );
	return static_cast<Ty &&>(x);
}

}  // namespace nstd

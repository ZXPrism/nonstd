#pragma once

#include <util/nstd_type_traits.h>

namespace nstd {

template<typename Ty>
constexpr Ty &&forward(remove_reference_t<Ty> &x) noexcept {  // overload accepts lvalue
	return static_cast<Ty &&>(x);
}

template<typename Ty>
constexpr Ty &&forward(remove_reference_t<Ty> &&x) noexcept {  // overload accepts rvalue
	static_assert(!is_lvalue_reference_v<Ty>, "attempting to forward a rvalue as a lvalue!");
	return static_cast<Ty &&>(x);
}

}  // namespace nstd

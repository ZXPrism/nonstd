#pragma once

namespace nstd {

// === integral_constant BEGINS ===
template<typename Ty, Ty val>
struct integral_constant {
	using value_type = Ty;
	using type = integral_constant;  // injected-class-name; equivalent to integral_constant<Ty, value>

	static constexpr Ty value = val;
	constexpr operator value_type() const noexcept {
		return value;
	}

	constexpr value_type operator()() const noexcept {
		return value;
	}
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template<bool val>
using bool_constant = integral_constant<bool, val>;
// === integral_constant ENDS ===

// === is_same BEGINS ===
template<typename Ty1, typename Ty2>
struct is_same : false_type {
};

template<typename Ty>
struct is_same<Ty, Ty> : true_type {
};

template<typename Ty1, typename Ty2>
constexpr bool is_same_v = is_same<Ty1, Ty2>::value;
// === is_same ENDS ===

}  // namespace nstd

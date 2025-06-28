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

// === conditional BEGINS ===
template<bool cond, typename Ty1, typename Ty2>
struct conditional {
	using type = Ty1;
};

template<typename Ty1, typename Ty2>
struct conditional<false, Ty1, Ty2> {
	using type = Ty2;
};

template<bool cond, typename Ty1, typename Ty2>
using conditional_t = typename conditional<cond, Ty1, Ty2>::type;
// === conditional ENDS ===

// is_const BEGINS
template<typename Ty>
struct is_const : false_type {
};

template<typename Ty>
struct is_const<const Ty> : true_type {
};

template<typename Ty>
constexpr bool is_const_v = is_const<Ty>::value;
// is_const ENDS

// is_volatile BEGINS
template<typename Ty>
struct is_volatile : false_type {
};

template<typename Ty>
struct is_volatile<volatile Ty> : true_type {
};

template<typename Ty>
constexpr bool is_volatile_v = is_volatile<Ty>::value;
// is_volatile ENDS

// remove_const BEGINS
template<typename Ty>
struct remove_const {
	using type = Ty;
};

template<typename Ty>
struct remove_const<const Ty> {
	using type = Ty;
};

template<typename Ty>
using remove_const_t = typename remove_const<Ty>::type;
// remove_const ENDS

// remove_volatile BEGINS
template<typename Ty>
struct remove_volatile {
	using type = Ty;
};

template<typename Ty>
struct remove_volatile<volatile Ty> {
	using type = Ty;
};

template<typename Ty>
using remove_volatile_t = typename remove_volatile<Ty>::type;
// remove_volatile ENDS

// remove_cv BEGINS
template<typename Ty>
struct remove_cv {
	using type = Ty;
};

template<typename Ty>
struct remove_cv<const Ty> {
	using type = Ty;
};

template<typename Ty>
struct remove_cv<volatile Ty> {
	using type = Ty;
};

template<typename Ty>
struct remove_cv<const volatile Ty> {
	using type = Ty;
};

template<typename Ty>
using remove_cv_t = typename remove_cv<Ty>::type;
// remove_cv ENDS

}  // namespace nstd

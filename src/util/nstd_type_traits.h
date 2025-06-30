#pragma once

#include <util/nstd_stddef.h>

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
struct is_same : false_type {};

template<typename Ty>
struct is_same<Ty, Ty> : true_type {};

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
struct is_const : false_type {};

template<typename Ty>
struct is_const<const Ty> : true_type {};

template<typename Ty>
constexpr bool is_const_v = is_const<Ty>::value;
// is_const ENDS

// is_volatile BEGINS
template<typename Ty>
struct is_volatile : false_type {};

template<typename Ty>
struct is_volatile<volatile Ty> : true_type {};

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

// add_const BEGINS
template<typename Ty>
struct add_const {
	using type = const Ty;
};

template<typename Ty>
using add_const_t = typename add_const<Ty>::type;
// add_const ENDS

// add_volatile BEGINS
template<typename Ty>
struct add_volatile {
	using type = volatile Ty;
};

template<typename Ty>
using add_volatile_t = typename add_volatile<Ty>::type;
// add_volatile ENDS

// add_cv BEGINS
template<typename Ty>
struct add_cv {
	using type = const volatile Ty;
};

template<typename Ty>
using add_cv_t = typename add_cv<Ty>::type;
// add_cv ENDS

// remove_reference BEGINS
template<typename Ty>
struct remove_reference {
	using type = Ty;
};

template<typename Ty>
struct remove_reference<Ty &> {
	using type = Ty;
};

template<typename Ty>
struct remove_reference<Ty &&> {
	using type = Ty;
};

template<typename Ty>
using remove_reference_t = typename remove_reference<Ty>::type;
// remove_reference ENDS

// is_array BEGINS
template<typename Ty>
struct is_array : false_type {};

template<typename Ty>
struct is_array<Ty[]> : true_type {};

template<typename Ty, size_t N>
struct is_array<Ty[N]> : true_type {};

template<typename Ty>
constexpr bool is_array_v = is_array<Ty>::value;
// is_array ENDS

// is_pointer BEGINS
template<typename Ty>
struct is_pointer : false_type {};

template<typename Ty>
struct is_pointer<Ty *> : true_type {};

template<typename Ty>
struct is_pointer<Ty *const> : true_type {};

template<typename Ty>
struct is_pointer<Ty *volatile> : true_type {};

template<typename Ty>
struct is_pointer<Ty *const volatile> : true_type {};

template<typename Ty>
constexpr bool is_pointer_v = is_pointer<Ty>::value;
// is_pointer ENDS

// is_reference BEGINS
template<typename Ty>
struct is_reference : false_type {};

template<typename Ty>
struct is_reference<Ty &> : true_type {};

template<typename Ty>
struct is_reference<Ty &&> : true_type {};

template<typename Ty>
constexpr bool is_reference_v = is_reference<Ty>::value;
// is_reference ENDS

// type_identity BEGINS
template<typename Ty>
struct type_identity {
	using type = Ty;
};

template<typename Ty>
using type_identity_t = typename type_identity<Ty>::type;
// type_identity ENDS

// remove_pointer BEGINS
template<typename Ty>
struct remove_pointer {
	using type = Ty;
};

template<typename Ty>
struct remove_pointer<Ty *> {
	using type = Ty;
};

template<typename Ty>
struct remove_pointer<Ty *const> {
	using type = Ty;
};

template<typename Ty>
struct remove_pointer<Ty *volatile> {
	using type = Ty;
};

template<typename Ty>
struct remove_pointer<Ty *const volatile> {
	using type = Ty;
};

template<typename Ty>
using remove_pointer_t = typename remove_pointer<Ty>::type;
// remove_pointer ENDS

// add_pointer BEGINS
namespace internal {

template<typename Ty>
auto try_add_pointer(int) -> type_identity<remove_reference_t<Ty> *>;

template<typename Ty>
auto try_add_pointer(...) -> type_identity<Ty>;

}  // namespace internal

template<typename Ty>
struct add_pointer : decltype(internal::try_add_pointer<Ty>(0)) {};

template<typename Ty>
using add_pointer_t = typename add_pointer<Ty>::type;
// add_pointer ENDS

// decay BEGINS
// template<typename Ty>
// struct decay {
// private:
// public:
// 	using type = Ty;
// };

// template<typename Ty>
// using decay_t = typename decay<Ty>::type;
// decay ENDS

}  // namespace nstd

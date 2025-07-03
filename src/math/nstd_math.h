#pragma once

namespace nstd {

// TODO: constrain Ty to signed numbers
template<typename Ty>
constexpr Ty abs(Ty x) {
	return (x < 0 ? -x : x);
}

template<typename Ty>
constexpr Ty max(Ty lhs, Ty rhs) {
	return (lhs > rhs ? lhs : rhs);
}

template<typename Ty>
constexpr Ty min(Ty lhs, Ty rhs) {
	return (lhs < rhs ? lhs : rhs);
}

// TODO: constrain Ty to floating numbers
template<typename Ty>
constexpr bool is_approx(Ty lhs, Ty rhs, Ty relative_tolerance) {
	return abs(lhs - rhs) <= max(abs(lhs), abs(rhs)) * relative_tolerance;
}

}  // namespace nstd

#pragma once

namespace nstd {

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

}  // namespace nstd

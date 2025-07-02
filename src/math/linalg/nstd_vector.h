#pragma once

#include <util/nstd_stddef.h>
#include <util/nstd_type_traits.h>

#include <utility>

namespace nstd {

namespace linalg {

template<typename Derived, typename Ty, size_t N>
class vector_base {
private:
	Ty _Data[N];

public:
	template<typename... Args>
	    requires(sizeof...(Args) == N && conjunction_v<is_convertible<Args, Ty>...>)
	constexpr vector_base(Args &&...args)
	    : _Data{ std::forward<Args>(args)... } {
	}

	consteval size_t size() const {
		return N;
	}
};

template<typename Ty, size_t N>
class vector : public vector_base<vector<Ty, N>, Ty, N> {
private:
	;

public:
	using vector_base<vector<Ty, N>, Ty, N>::vector_base;
};

template<typename Ty, size_t N>
class vector_v2 : public vector_base<vector<Ty, N>, Ty, N> {
private:
};

using vector2i = vector<int, 2>;
using vector3i = vector<int, 3>;
using vector4i = vector<int, 4>;
using vector2ll = vector<long long, 2>;
using vector3ll = vector<long long, 3>;
using vector4ll = vector<long long, 4>;
using vector2f = vector<float, 2>;
using vector3f = vector<float, 3>;
using vector4f = vector<float, 4>;
using vector2d = vector<double, 2>;
using vector3d = vector<double, 3>;
using vector4d = vector<double, 4>;

}  // namespace linalg

}  // namespace nstd

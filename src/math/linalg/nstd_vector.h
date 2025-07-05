#pragma once

#include <math/nstd_math.h>
#include <util/nstd_stddef.h>
#include <util/nstd_type_traits.h>
#include <util/nstd_utility.h>

// TODO: REMOVE these deps in future versions
#include <cassert>
#include <cmath>
#include <initializer_list>

namespace nstd {

namespace linalg {  // without special reminder, assume using a right-handed Cartesian coordinate system

template<typename Derived, typename Ty, size_t N, bool simd>
class vector_base {
protected:
	Ty _Data[N]{};

public:
	using value_type = Ty;

	constexpr vector_base() = default;

	template<typename... Args>
	    requires(sizeof...(Args) == N && conjunction_v<is_convertible<Args, Ty>...>)
	constexpr vector_base(Args &&...args)
	    : _Data{ forward<Args>(args)... } {
	}

	template<typename _Derived, bool _simd>
	constexpr vector_base(const vector_base<_Derived, Ty, N, _simd> &vec)
	    : _Data(vec._Data) {
	}

	constexpr vector_base(const std::initializer_list<Ty> &args) {
		assert(args.size() == N);
		for (size_t i = 0; i < N; i++) {
			_Data[i] = args.begin()[i];
		}
	}

	constexpr Ty operator[](size_t i) const {
		assert(i < N);
		return _Data[i];
	}

	constexpr Ty &operator[](size_t i) {
		assert(i < N);
		return _Data[i];
	}

	constexpr const Ty *data() const {
		return _Data;
	}

	constexpr Ty norm() const {
		Ty res{};
		for (size_t i = 0; i < N; i++) {
			res += _Data[i] * _Data[i];
		}
		return std::sqrt(res);
	}

	constexpr Ty norm_squared() const {
		Ty res{};
		for (size_t i = 0; i < N; i++) {
			res += _Data[i] * _Data[i];
		}
		return res;
	}

	constexpr void normalize() {
		Ty length = norm();
		if (!is_approx(length, 0.0f, static_cast<Ty>(1e-5f))) {
			for (size_t i = 0; i < N; i++) {
				_Data[i] /= length;
			}
		}
	}

	template<typename _Derived, typename _Ty, size_t _N, bool _simd>
	constexpr friend _Derived normalized(const vector_base<_Derived, _Ty, _N, _simd> &vec);

	template<typename _Derived, typename _Ty, size_t _N, bool _simd>
	constexpr friend _Ty dot(const vector_base<_Derived, _Ty, _N, _simd> &lhs, const vector_base<_Derived, _Ty, _N, _simd> &rhs);

	template<typename _Derived, typename _Ty, size_t _N, bool _simd>
	    requires(_N == 3)
	constexpr friend Derived cross(const vector_base<_Derived, _Ty, _N, _simd> &lhs,
	                               const vector_base<_Derived, _Ty, _N, _simd> &rhs);

	static consteval size_t size() {
		return N;
	}
};

template<typename Derived, typename Ty, size_t N, bool simd>
constexpr Derived normalized(const vector_base<Derived, Ty, N, simd> &vec) {
	Derived normalized_vec(vec);
	normalized_vec.normalize();
	return normalized_vec;
}

template<typename Derived, typename Ty, size_t N, bool simd>
constexpr Ty dot(const vector_base<Derived, Ty, N, simd> &lhs, const vector_base<Derived, Ty, N, simd> &rhs) {
	Ty res{};
	for (size_t i = 0; i < N; i++) {
		res += lhs._Data[i] * rhs._Data[i];
	}
	return res;
}

template<typename _Derived, typename _Ty, size_t _N, bool _simd>
    requires(_N == 3)
constexpr _Derived cross(const vector_base<_Derived, _Ty, _N, _simd> &lhs,
                         const vector_base<_Derived, _Ty, _N, _simd> &rhs) {
	return { lhs[1] * rhs[2] - lhs[2] * rhs[1],
		     lhs[2] * rhs[0] - lhs[0] * rhs[2],
		     lhs[0] * rhs[1] - lhs[1] * rhs[0] };
}

template<typename Ty, size_t N, bool simd = true>
class vector : public vector_base<vector<Ty, N>, Ty, N, simd> {
public:
	using vector_base<vector, Ty, N, simd>::vector_base;
	constexpr vector(const vector_base<vector, Ty, N, simd> &vec_base)
	    : vector_base<vector, Ty, N, simd>(vec_base) {}
};

template<typename Ty, size_t N, bool simd = true>
class vector_v2 : public vector_base<vector<Ty, N>, Ty, N, simd> {
public:
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

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
	Ty _Data[N];

public:
	using value_type = Ty;

	constexpr vector_base() = default;

	constexpr explicit vector_base(Ty &&val) {
		for (size_t i = 0; i < N; i++) {
			_Data[i] = val;
		}
	}

	template<typename... Args>
	    requires(sizeof...(Args) == N && conjunction_v<is_convertible<Args, Ty>...>)
	constexpr vector_base(Args &&...args)
	    : _Data{ forward<Args>(args)... } {
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

	constexpr Derived operator+(const Derived &rhs) const {
		return static_cast<const Derived *>(this)->_impl_add(rhs);
	}

	constexpr Derived operator-(const Derived &rhs) const {
		return static_cast<const Derived *>(this)->_impl_sub(rhs);
	}

	constexpr Derived operator*(Ty scalar) const {
		return static_cast<const Derived *>(this)->_impl_mul_scalar(scalar);
	}

	constexpr friend Derived operator*(Ty scalar, const Derived &vec) {
		return _impl_vec_mul_scalar(scalar, vec);
	}

	constexpr Ty norm() const {
		Ty res{};
		for (size_t i = 0; i < N; i++) {
			res += _Data[i] * _Data[i];
		}
		return std::sqrt(res);  // TODO: use nstd::sqrt
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

	template<typename _Derived>
	constexpr friend _Derived normalized(const _Derived &vec);

	template<typename _Derived>
	constexpr friend typename _Derived::value_type dot(const _Derived &lhs, const _Derived &rhs);

	template<typename _Derived>
	    requires(_Derived::size() == 3)
	constexpr friend _Derived cross(const _Derived &lhs, const _Derived &rhs);

	static consteval size_t size() {
		return N;
	}
};

template<typename Derived>
constexpr Derived normalized(const Derived &vec) {
	Derived normalized_vec(vec);
	normalized_vec.normalize();
	return normalized_vec;
}

template<typename Derived>
constexpr typename Derived::value_type dot(const Derived &lhs, const Derived &rhs) {
	typename Derived::value_type res{};
	for (size_t i = 0; i < Derived::size(); i++) {
		res += lhs._Data[i] * rhs._Data[i];
	}
	return res;
}

template<typename Derived>
    requires(Derived::size() == 3)
constexpr Derived cross(const Derived &lhs, const Derived &rhs) {
	return { lhs[1] * rhs[2] - lhs[2] * rhs[1],
		     lhs[2] * rhs[0] - lhs[0] * rhs[2],
		     lhs[0] * rhs[1] - lhs[1] * rhs[0] };
}

template<typename Ty, size_t N, bool simd>
class vector : public vector_base<vector<Ty, N, simd>, Ty, N, simd> {
	using base = vector_base<vector, Ty, N, simd>;

public:
	using value_type = Ty;
	using base::base;

	constexpr vector _impl_add(const vector &rhs) const {
		vector res;
		for (size_t i = 0; i < N; i++) {
			res._Data[i] = base::_Data[i] + rhs._Data[i];
		}
		return res;
	}

	constexpr vector _impl_sub(const vector &rhs) const {
		vector res;
		for (size_t i = 0; i < N; i++) {
			res._Data[i] = base::_Data[i] - rhs._Data[i];
		}
		return res;
	}

	constexpr vector _impl_mul_scalar(Ty scalar) const {
		vector res;
		for (size_t i = 0; i < N; i++) {
			res._Data[i] = base::_Data[i] * scalar;
		}
		return res;
	}

	template<typename _Ty, size_t _N, bool _simd>
	friend constexpr vector<_Ty, _N, _simd> _impl_vec_mul_scalar(_Ty scalar, const vector<_Ty, _N, _simd> &vec);
};

template<typename Ty, size_t N, bool simd>
constexpr vector<Ty, N, simd> _impl_vec_mul_scalar(Ty scalar, const vector<Ty, N, simd> &vec) {
	vector<Ty, N, simd> res;
	for (size_t i = 0; i < N; i++) {
		res._Data[i] = vec._Data[i] * scalar;
	}
	return res;
}

template<typename Ty, size_t N, bool simd>
class vector_v2 : public vector_base<vector<Ty, N, simd>, Ty, N, simd> {
public:
};

using vector2i = vector<int, 2, false>;
using vector3i = vector<int, 3, false>;
using vector4i = vector<int, 4, false>;
using vector2ll = vector<long long, 2, false>;
using vector3ll = vector<long long, 3, false>;
using vector4ll = vector<long long, 4, false>;
using vector2f = vector<float, 2, false>;
using vector3f = vector<float, 3, false>;
using vector4f = vector<float, 4, false>;
using vector2d = vector<double, 2, false>;
using vector3d = vector<double, 3, false>;
using vector4d = vector<double, 4, false>;

}  // namespace linalg

}  // namespace nstd

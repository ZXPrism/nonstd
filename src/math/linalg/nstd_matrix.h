#pragma once

#include <math/nstd_math.h>
#include <util/nstd_stddef.h>
#include <util/nstd_type_traits.h>
#include <util/nstd_utility.h>

// TODO: REMOVE these deps in future versions
#include <cassert>
#include <cmath>
#include <initializer_list>

/*
 * ! assumptions !
 * 1. use a right-handed Cartesian coordinate system
 * 2. vectors are all column vectors (i.e. Nx1)
 * 3. use row-major ordering storage layout
 */

namespace nstd {

namespace linalg {  // without special reminder, assume using a right-handed Cartesian coordinate system

template<typename Derived, typename Ty, size_t M, size_t N, bool simd>
    requires(M > 0 && N > 0)
class matrix_base {

	template<typename _Ty, size_t _N>
	struct matrix_visitor {
		_Ty *_Data;

		explicit matrix_visitor(_Ty *data_ptr)
		    : _Data(data_ptr) {}

		_Ty &operator[](size_t i) {
			assert(i < _N);
			return _Data[i];
		}
	};

protected:
	Ty _Data[M][N];

public:
	using value_type = Ty;

	constexpr matrix_base() = default;

	constexpr explicit matrix_base(Ty &&val) {
		if constexpr (M == N) {  // diagonal init
			for (size_t i = 0; i < M; i++) {
				_Data[i][i] = val;
			}
		} else {  // fallback to full init
			for (size_t i = 0; i < M; i++) {
				for (size_t j = 0; j < N; j++) {
					_Data[i][j] = val;
				}
			}
		}
	}

	template<typename... Args>  // should be given in row-major order
	    requires(sizeof...(Args) == M * N && conjunction_v<is_convertible<Args, Ty>...>)
	constexpr matrix_base(Args &&...args)
	    : _Data{ forward<Args>(args)... } {
	}

	constexpr matrix_base(const std::initializer_list<Ty> &args) {
		assert(args.size() == M * N);
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				_Data[i][j] = args.begin()[i * N + j];
			}
		}
	}

	constexpr decltype(auto) operator[](size_t i) const {
		assert(i < M);
		if constexpr (N != 1) {
			return matrix_visitor<const Ty, N>(_Data[i]);
		} else {
			return _Data[i][0];
		}
	}

	constexpr decltype(auto) operator[](size_t i) {
		assert(i < M);
		if constexpr (N != 1) {
			return matrix_visitor<Ty, N>(_Data[i]);
		} else {
			return _Data[i][0];
		}
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

	// template<typename Mat>
	//     requires (..)
	// constexpr auto operator*(const Mat &rhs) const {
	// 	return static_cast<const Derived *>(this)->_impl_mul(rhs);
	// }

	constexpr Derived operator*(Ty scalar) const {
		return static_cast<const Derived *>(this)->_impl_mul_scalar(scalar);
	}

	constexpr friend Derived operator*(Ty scalar, const Derived &rhs) {
		return _impl_scalar_mul_mat(scalar, rhs);
	}

	static consteval size_t size_row() {
		return M;
	}

	static consteval size_t size_col() {
		return N;
	}

	template<size_t _ = M>
	    requires(N == 1)
	constexpr Ty norm() const {
		Ty res{};
		for (size_t i = 0; i < M; i++) {
			res += _Data[i][0] * _Data[i][0];
		}
		return std::sqrt(res);  // TODO: use nstd::sqrt
	}

	template<size_t _ = M>
	    requires(N == 1)
	constexpr Ty norm_squared() const {
		Ty res{};
		for (size_t i = 0; i < M; i++) {
			res += _Data[i][0] * _Data[i][0];
		}
		return res;
	}

	template<size_t _ = M>
	    requires(N == 1)
	constexpr void normalize() {
		Ty length = norm();
		if (!is_approx(length, 0.0f, static_cast<Ty>(1e-5f))) {
			for (size_t i = 0; i < M; i++) {
				_Data[i][0] /= length;
			}
		}
	}

	template<typename _Derived>
	    requires(_Derived::size_col() == 1)
	constexpr friend _Derived normalized(const _Derived &vec);

	template<typename _Derived>
	    requires(_Derived::size_col() == 1)
	constexpr friend typename _Derived::value_type dot(const _Derived &lhs, const _Derived &rhs);

	template<typename _Derived>
	    requires(_Derived::size_row() == 3 && _Derived::size_col() == 1)
	constexpr friend _Derived cross(const _Derived &lhs, const _Derived &rhs);

	static constexpr Derived zeros() {
		Derived res;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				res._Data[i][j] = static_cast<Ty>(0);
			}
		}
		return res;
	}

	static constexpr Derived ones() {
		Derived res;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				res._Data[i][j] = static_cast<Ty>(1);
			}
		}
		return res;
	}

	template<size_t _M = M, size_t _N = N>  // diagonal init
	    requires(_M == _N)
	static constexpr Derived identity() {
		Derived res;
		for (size_t i = 0; i < M; i++) {
			res._Data[i][i] = static_cast<Ty>(1);
		}
		return res;
	}
};

template<typename _Derived>
    requires(_Derived::size_col() == 1)
constexpr _Derived normalized(const _Derived &vec) {
	_Derived normalized_vec(vec);
	normalized_vec.normalize();
	return normalized_vec;
}

template<typename _Derived>
    requires(_Derived::size_col() == 1)
constexpr typename _Derived::value_type dot(const _Derived &lhs, const _Derived &rhs) {
	typename _Derived::value_type res{};
	for (size_t i = 0; i < _Derived::size_row(); i++) {
		res += lhs._Data[i][0] * rhs._Data[i][0];
	}
	return res;
}

template<typename _Derived>
    requires(_Derived::size_row() == 3 && _Derived::size_col() == 1)
constexpr _Derived cross(const _Derived &lhs, const _Derived &rhs) {
	return { lhs._Data[1][0] * rhs._Data[2][0] - lhs._Data[2][0] * rhs._Data[1][0],
		     lhs._Data[2][0] * rhs._Data[0][0] - lhs._Data[0][0] * rhs._Data[2][0],
		     lhs._Data[0][0] * rhs._Data[1][0] - lhs._Data[1][0] * rhs._Data[0][0] };
}

template<typename Ty, size_t M, size_t N, bool simd>
class matrix : public matrix_base<matrix<Ty, M, N, simd>, Ty, M, N, simd> {
	using base = matrix_base<matrix, Ty, M, N, simd>;

public:
	using value_type = Ty;

	using base::base;

	constexpr matrix _impl_add(const matrix &rhs) const {
		matrix res;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				res._Data[i][j] = base::_Data[i][j] + rhs._Data[i][j];
			}
		}
		return res;
	}

	constexpr matrix _impl_sub(const matrix &rhs) const {
		matrix res;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				res._Data[i][j] = base::_Data[i][j] - rhs._Data[i][j];
			}
		}
		return res;
	}

	template<typename Mat>
	constexpr matrix _impl_mul(const Mat &rhs) const {
		matrix<Ty, M, Mat::N, simd> res;

		return res;
	}

	constexpr matrix _impl_mul_scalar(Ty scalar) const {
		matrix res;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				res._Data[i][j] = base::_Data[i][j] * scalar;
			}
		}
		return res;
	}

	template<typename _Ty, size_t _M, size_t _N, bool _simd>
	friend constexpr matrix<_Ty, _M, _N, _simd> _impl_scalar_mul_mat(_Ty scalar, const matrix<_Ty, _M, _N, _simd> &vec);
};

template<typename Ty, size_t M, size_t N, bool simd>
constexpr matrix<Ty, M, N, simd> _impl_scalar_mul_mat(Ty scalar, const matrix<Ty, M, N, simd> &vec) {
	matrix<Ty, M, N, simd> res;
	for (size_t i = 0; i < M; i++) {
		for (size_t j = 0; j < N; j++) {
			res._Data[i][j] = vec._Data[i][j] * scalar;
		}
	}
	return res;
}

template<typename Ty, size_t M, size_t N, bool simd>
class matrix_v2 : public matrix_base<matrix<Ty, M, N, simd>, Ty, M, N, simd> {
public:
};

using matrix2i = matrix<int, 2, 2, false>;
using matrix3i = matrix<int, 3, 3, false>;
using matrix4i = matrix<int, 4, 4, false>;
using matrix2ll = matrix<long long, 2, 2, false>;
using matrix3ll = matrix<long long, 3, 3, false>;
using matrix4ll = matrix<long long, 4, 4, false>;
using matrix2f = matrix<float, 2, 2, false>;
using matrix3f = matrix<float, 3, 3, false>;
using matrix4f = matrix<float, 4, 4, false>;
using matrix2d = matrix<double, 2, 2, false>;
using matrix3d = matrix<double, 3, 3, false>;
using matrix4d = matrix<double, 4, 4, false>;

}  // namespace linalg

}  // namespace nstd

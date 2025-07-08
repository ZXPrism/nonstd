#pragma once

#include <math/nstd_math.h>
#include <util/nstd_stddef.h>
#include <util/nstd_type_traits.h>
#include <util/nstd_utility.h>

// TODO: REMOVE these deps in future versions
#include <cassert>
#include <cmath>

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
				for (size_t j = 0; j < M; j++) {
					if (i == j) {
						_Data[i][j] = val;
					} else {
						_Data[i][j] = static_cast<Ty>(0);
					}
				}
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
		return static_cast<const Ty *>(_Data);
	}

	constexpr Derived operator+(const Derived &rhs) const {
		return static_cast<const Derived *>(this)->_impl_add(rhs);
	}

	constexpr Derived operator-(const Derived &rhs) const {
		return static_cast<const Derived *>(this)->_impl_sub(rhs);
	}

	template<typename Mat>
	    requires(Mat::size_row() == N)
	constexpr auto operator*(const Mat &rhs) const {
		return static_cast<const Derived *>(this)->_impl_mul(rhs);
	}

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

	constexpr Derived normalized() const {
		Derived normalized_vec(*static_cast<const Derived *>(this));
		normalized_vec.normalize();
		return normalized_vec;
	}

	template<size_t _ = M>
	    requires(N == 1)
	constexpr Ty dot(const Derived &rhs) const {
		Ty res{};
		for (size_t i = 0; i < M; i++) {
			res += _Data[i][0] * rhs._Data[i][0];
		}
		return res;
	}

	template<size_t _ = M>
	    requires(M == 3 && N == 1)
	constexpr Derived cross(const Derived &rhs) const {
		return { _Data[1][0] * rhs._Data[2][0] - _Data[2][0] * rhs._Data[1][0],
			     _Data[2][0] * rhs._Data[0][0] - _Data[0][0] * rhs._Data[2][0],
			     _Data[0][0] * rhs._Data[1][0] - _Data[1][0] * rhs._Data[0][0] };
	}

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
			for (size_t j = 0; j < M; j++) {
				if (i == j) {
					res._Data[i][j] = static_cast<Ty>(1);
				} else {
					res._Data[i][j] = static_cast<Ty>(0);
				}
			}
		}
		return res;
	}
};

template<typename Derived>
constexpr typename Derived::value_type dot(const Derived &lhs, const Derived &rhs) {
	return lhs.dot(rhs);
}

template<typename Derived>
constexpr Derived cross(const Derived &lhs, const Derived &rhs) {
	return lhs.cross(rhs);
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
	constexpr auto _impl_mul(const Mat &rhs) const {
		auto res = matrix<Ty, M, Mat::size_col(), simd>::zeros();
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < Mat::size_col(); j++) {
				for (size_t k = 0; k < N; k++) {
					res._Data[i][j] += base::_Data[i][k] * rhs._Data[k][j];
				}
			}
		}
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
};

template<typename Ty, size_t M, size_t N, bool simd>
constexpr matrix<Ty, M, N, simd> _impl_scalar_mul_mat(Ty scalar, const matrix<Ty, M, N, simd> &mat) {
	return mat * scalar;
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

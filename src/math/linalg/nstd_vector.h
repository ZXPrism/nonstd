#pragma once

#include <util/nstd_stddef.h>
#include <util/nstd_type_traits.h>
#include <util/nstd_utility.h>

// TODO: REMOVE these deps in future versions
#include <cassert>
#include <cmath>
#include <initializer_list>

namespace nstd {

namespace linalg {

template<typename Derived, typename Ty, size_t N, bool simd>
class vector_base {
private:
	Ty _Data[N]{};

public:
	constexpr vector_base() = default;

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

	constexpr Ty normalize() {
		Ty length = norm();
		if (length) {
			for (size_t i = 0; i < N; i++) {
				_Data[i] /= length;
			}
		}
	}

	constexpr friend Derived normalized(const vector_base &vec) {
		Derived normalized_vec = vec;
		Ty length = normalized_vec.norm();
		if (length) {
			for (size_t i = 0; i < N; i++) {
				normalized_vec._Data[i] /= length;
			}
		}
		return normalized_vec;
	}

	constexpr friend Ty dot(const vector_base &lhs, const vector_base &rhs) {
		Ty res{};
		for (size_t i = 0; i < N; i++) {
			res += lhs._Data[i] * rhs._Data[i];
		}
		return res;
	}

	template<size_t _N>
	    requires(_N == 3)
	constexpr friend Derived cross(const vector_base<Derived, Ty, _N, simd> &lhs,
	                               const vector_base<Derived, Ty, _N, simd> &rhs) {
		return {};
	}

	static consteval size_t size() {
		return N;
	}
};

template<typename Ty, size_t N, bool simd = true>
class vector : public vector_base<vector<Ty, N>, Ty, N, simd> {
public:
	using vector_base<vector<Ty, N>, Ty, N, simd>::vector_base;
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

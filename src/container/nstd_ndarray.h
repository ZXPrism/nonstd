#pragma once

#include <util/nstd_type_traits.h>

// TODO: REMOVE this dep in future versions
#include <cassert>
#include <stdexcept>

namespace nstd {

template<size_t First, size_t... Remain>
consteval size_t get_first() {
	return First;
}

template<typename Ty, bool exception, size_t... DimSize>
    requires(sizeof...(DimSize) > 0)
class basic_ndarray {
	template<typename _Ty, size_t N, size_t CurrDim, size_t... RemainDim>
	struct basic_ndarray_visitor {
		_Ty *_Data;
		size_t _Offset;

		constexpr basic_ndarray_visitor(_Ty *data, size_t offset) noexcept(!exception)
		    : _Data(data)
		    , _Offset(offset) {}

		constexpr basic_ndarray_visitor<_Ty, N - 1, RemainDim...> operator[](size_t i) noexcept(!exception) {
			if constexpr (exception) {
				if (i >= CurrDim) {
					throw std::runtime_error("basic_ndarray out of bounds!");
				}
			}
			return { _Data, _Offset + i * (RemainDim * ...) };
		}
	};

	template<typename _Ty, size_t CurrDim>
	struct basic_ndarray_visitor<_Ty, 0, CurrDim> {
		_Ty *_Data;
		size_t _Offset;

		constexpr basic_ndarray_visitor(_Ty *data, size_t offset) noexcept(!exception)
		    : _Data(data)
		    , _Offset(offset) {}

		constexpr _Ty &operator[](size_t i) noexcept(!exception) {
			if constexpr (exception) {
				if (i >= CurrDim) {
					throw std::runtime_error("basic_ndarray out of bounds!");
				}
			}
			return _Data[_Offset + i];
		}
	};

private:
	Ty _Data[(DimSize * ...)]{};

public:
	constexpr basic_ndarray() = default;

	constexpr decltype(auto) operator[](size_t i) const noexcept(!exception) {
		basic_ndarray_visitor<const Ty, sizeof...(DimSize) - 1, DimSize...> visitor{
			_Data, 0
		};
		return visitor[i];
	}

	constexpr decltype(auto) operator[](size_t i) noexcept(!exception) {
		basic_ndarray_visitor<Ty, sizeof...(DimSize) - 1, DimSize...> visitor{
			_Data, 0
		};
		return visitor[i];
	}

	static constexpr size_t arr_size = (DimSize * ...);
};

template<typename Ty, size_t... DimSize>
using ndarray = basic_ndarray<Ty, false, DimSize...>;

template<typename Ty, size_t... DimSize>
using ndarray_strict = basic_ndarray<Ty, true, DimSize...>;

}  // namespace nstd

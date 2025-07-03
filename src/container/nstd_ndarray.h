#pragma once

#include <util/nstd_type_traits.h>

// TODO: REMOVE this dep in future versions
#include <cassert>

namespace nstd {

template<size_t First, size_t... Remain>
consteval size_t get_first() {
	return First;
}

template<typename Ty, size_t... DimSize>
    requires(sizeof...(DimSize) > 0)
class ndarray {
	template<typename _Ty, size_t N, size_t CurrDim, size_t... RemainDim>
	struct ndarray_visitor {
		_Ty *_Data;
		size_t _Offset;

		constexpr ndarray_visitor(_Ty *data, size_t offset)
		    : _Data(data)
		    , _Offset(offset) {}

		constexpr ndarray_visitor<_Ty, N - 1, RemainDim...> operator[](size_t i) {
			assert(i < CurrDim);
			return { _Data, _Offset + i * (RemainDim * ...) };
		}
	};

	template<typename _Ty, size_t CurrDim>
	struct ndarray_visitor<_Ty, 0, CurrDim> {
		_Ty *_Data;
		size_t _Offset;

		constexpr ndarray_visitor(_Ty *data, size_t offset)
		    : _Data(data)
		    , _Offset(offset) {}

		constexpr _Ty &operator[](size_t i) {
			assert(i < CurrDim);
			return _Data[_Offset + i];
		}
	};

private:
	Ty _Data[(DimSize * ...)]{};

public:
	constexpr ndarray() = default;

	constexpr auto operator[](size_t i) const {
		ndarray_visitor<const Ty, sizeof...(DimSize) - 1, DimSize...> visitor{
			_Data, 0
		};
		return visitor[i];
	}

	constexpr auto operator[](size_t i) {
		ndarray_visitor<Ty, sizeof...(DimSize) - 1, DimSize...> visitor{
			_Data, 0
		};
		return visitor[i];
	}

	static constexpr size_t arr_size = (DimSize * ...);
};

}  // namespace nstd

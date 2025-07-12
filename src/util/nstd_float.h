#pragma once

namespace nstd {

namespace internal {

union float_unpacker {
	float _Num;
	unsigned _Raw;
};

union double_unpacker {
	double _Num;
	unsigned long long _Raw;
};

}  // namespace internal

// isnan BEGINS
constexpr bool isnan(float number) {
	const unsigned raw = internal::float_unpacker{ number }._Raw;
	const unsigned exp = (raw >> 23) & 0xff;
	const unsigned mantissa = raw & 0x7ff'fff;
	return exp == 0xff && mantissa != 0;
}

constexpr bool isnan(double number) {
	const unsigned long long raw = internal::double_unpacker{ number }._Raw;
	const unsigned exp = (raw >> 52) & 0x7ff;
	const unsigned long long mantissa = raw & 0xffff'ffff'ffff'f;
	return exp == 0x7ff && mantissa != 0;
}
// isnan ENDS

// isnan BEGINS
constexpr bool isinf(float number) {
	const unsigned raw = internal::float_unpacker{ number }._Raw;
	const unsigned exp = (raw >> 23) & 0xff;
	const unsigned mantissa = raw & 0x7ff'fff;
	return exp == 0xff && mantissa == 0;
}

constexpr bool isinf(double number) {
	const unsigned long long raw = internal::double_unpacker{ number }._Raw;
	const unsigned exp = (raw >> 52) & 0x7ff;
	const unsigned long long mantissa = raw & 0xffff'ffff'ffff'f;
	return exp == 0xff && mantissa == 0;
}
// isnan ENDS

// signbit BEGINS
constexpr bool signbit(float number) {
	return internal::float_unpacker{ number }._Raw >> 31;
}

constexpr bool signbit(double number) {
	return internal::double_unpacker{ number }._Raw >> 63;
}
// signbit ENDS

}  // namespace nstd

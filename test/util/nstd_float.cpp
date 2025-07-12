#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <util/nstd_float.h>

#include <cfenv>
#include <cmath>
#include <limits>

TEST_CASE("isnan") {
	CHECK_EQ(nstd::isnan(1.23f), std::isnan(1.23f));
	CHECK_EQ(nstd::isnan(1.23), std::isnan(1.23));
	CHECK_EQ(nstd::isnan(std::nanf("")), std::isnan(std::nanf("")));
	CHECK_EQ(nstd::isnan(std::nan("")), std::isnan(std::nan("")));
}

TEST_CASE("isinf") {
	constexpr float inff = std::numeric_limits<float>::infinity();
	constexpr float infd = std::numeric_limits<double>::infinity();
	CHECK_EQ(nstd::isinf(1.23f), std::isinf(1.23f));
	CHECK_EQ(nstd::isinf(1.23), std::isinf(1.23));
	CHECK_EQ(nstd::isinf(inff), std::isinf(inff));
	CHECK_EQ(nstd::isinf(infd), std::isinf(infd));
}

TEST_CASE("signbit") {
	CHECK_EQ(nstd::signbit(1.23f), std::signbit(1.23f));
	CHECK_EQ(nstd::signbit(-1.23), std::signbit(-1.23));
	CHECK_EQ(nstd::signbit(0.0f), std::signbit(0.0f));
	CHECK_EQ(nstd::signbit(-0.0f), std::signbit(-0.0f));
	CHECK_EQ(nstd::signbit(0.0), std::signbit(0.0));
	CHECK_EQ(nstd::signbit(-0.0), std::signbit(-0.0));
}

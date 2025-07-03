#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <math/nstd_math.h>
#include <cmath>

TEST_CASE("abs") {
	float x = 124.5;
	CHECK_EQ(nstd::abs(x), x);

	float y = -124.5;
	CHECK_EQ(nstd::abs(y), -y);

	CHECK_EQ(nstd::abs(x), std::abs(x));
	CHECK_EQ(nstd::abs(y), std::abs(y));

	int xi = 233;
	CHECK_EQ(nstd::abs(xi), xi);

	int yi = -233;
	CHECK_EQ(nstd::abs(yi), -yi);

	CHECK_EQ(nstd::abs(xi), std::abs(xi));
	CHECK_EQ(nstd::abs(yi), std::abs(yi));
}

TEST_CASE("max") {
	int x = -123, y = 666;
	CHECK_EQ(nstd::max(x, y), std::max(x, y));

	float xf = 1234.5, yf = -101.3;
	CHECK_EQ(nstd::max(xf, yf), std::max(xf, yf));
}

TEST_CASE("max") {
	int x = -123, y = 666;
	CHECK_EQ(nstd::min(x, y), std::min(x, y));

	float xf = 1234.5, yf = -101.3;
	CHECK_EQ(nstd::min(xf, yf), std::min(xf, yf));
}

TEST_CASE("is_approx") {
	CHECK(nstd::is_approx(1.3f, 1.30001f, 1e-5f));
	CHECK(!nstd::is_approx(1.3f, 1.301f, 1e-5f));
	CHECK(nstd::is_approx(63482.233f, 63481.123f, 1e-4f));
}

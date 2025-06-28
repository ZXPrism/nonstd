#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("Basic Arithmetic") {
	CHECK(1 + 1 == 2);
	CHECK(2 * 3 == 6);
	CHECK(10 / 2 == 5);
	CHECK(5 - 3 == 2);
}

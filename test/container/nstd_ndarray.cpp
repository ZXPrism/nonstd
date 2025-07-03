#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <container/nstd_ndarray.h>

TEST_CASE("init") {
	nstd::ndarray<int, 1, 1, 4, 5, 1, 4> arr;
	CHECK_EQ(decltype(arr)::arr_size, 80);
	CHECK_EQ(arr[0][0][2][3][0][2] = 31221, 31221);
}

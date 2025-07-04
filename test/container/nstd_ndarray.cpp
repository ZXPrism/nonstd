#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <container/nstd_ndarray.h>

// TODO: REMOVE this dep in future versions
#include <random>

TEST_CASE("zero init") {
	nstd::ndarray<int, 5, 6, 7> arr;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 7; k++) {
				CHECK_EQ(arr[i][j][k], 0);
			}
		}
	}
}

TEST_CASE("arr size") {
	nstd::ndarray<int, 5, 6, 7> arr;
	CHECK_EQ(decltype(arr)::arr_size, 5 * 6 * 7);
}

TEST_CASE("rw") {
	nstd::ndarray<int, 5, 6, 7> arr;

	std::random_device rd;
	std::mt19937_64 engine(rd());
	std::uniform_int_distribution<int> dist(-(1 << 30), 1 << 30);

	int vals[5][6][7];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 7; k++) {
				vals[i][j][k] = dist(engine);
				arr[i][j][k] = vals[i][j][k];
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 7; k++) {
				CHECK_EQ(arr[i][j][k], vals[i][j][k]);
			}
		}
	}
}

TEST_CASE("out of bounds") {
	nstd::ndarray_strict<int, 5, 6, 7> arr;
	CHECK_THROWS(arr[5][0][0]);
	CHECK_THROWS(arr[0][6][0]);
	CHECK_THROWS(arr[0][0][7]);
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include <container/nstd_ndarray.h>

ankerl::nanobench::Rng rng;

// bench_seqwr_1d BEGINS
void BM_plain_seqwr_1d() {
	int arr[16384]{};
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 16384; i++) {
		ankerl::nanobench::doNotOptimizeAway(arr[i]);
		arr[i] = 0xcafebabe;
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

void BM_nonstd_seqwr_1d() {
	nstd::ndarray<int, 16384> arr;
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 16384; i++) {
		ankerl::nanobench::doNotOptimizeAway(arr[i]);
		arr[i] = 0xcafebabe;
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

TEST_CASE("bench_seqwr_1d") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_seqwr_1d")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("plain / seqwr_1d", BM_plain_seqwr_1d);
	bench.run("nonstd / seqwr_1d", BM_nonstd_seqwr_1d);
}
// bench_seqwr_1d ENDS

// bench_seqwr_2d BEGINS
void BM_plain_seqwr_2d() {
	int arr[128][128]{};
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			ankerl::nanobench::doNotOptimizeAway(arr[i][j]);
			arr[i][j] = 0xcafebabe;
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

void BM_nonstd_seqwr_2d() {
	nstd::ndarray<int, 128, 128> arr;
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			ankerl::nanobench::doNotOptimizeAway(arr[i][j]);
			arr[i][j] = 0xcafebabe;
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

TEST_CASE("bench_seqwr_2d") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_seqwr_2d")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("plain / seqwr_2d", BM_plain_seqwr_2d);
	bench.run("nonstd / seqwr_2d", BM_nonstd_seqwr_2d);
}
// bench_seqwr_2d ENDS

// bench_seqwr_3d BEGINS
void BM_plain_seqwr_3d() {
	int arr[32][32][32]{};
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			for (int k = 0; k < 32; k++) {
				ankerl::nanobench::doNotOptimizeAway(arr[i][j][k]);
				arr[i][j][k] = 0xcafebabe;
			}
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

void BM_nonstd_seqwr_3d() {
	nstd::ndarray<int, 32, 32, 32> arr;
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			for (int k = 0; k < 32; k++) {
				ankerl::nanobench::doNotOptimizeAway(arr[i][j][k]);
				arr[i][j][k] = 0xcafebabe;
			}
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

TEST_CASE("bench_seqwr_3d") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_seqwr_3d")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("plain / seqwr_3d", BM_plain_seqwr_3d);
	bench.run("nonstd / seqwr_3d", BM_nonstd_seqwr_3d);
}
// bench_seqwr_3d ENDS

// bench_seqwr_4d BEGINS
void BM_plain_seqwr_4d() {
	int arr[16][16][16][16]{};
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				for (int m = 0; m < 16; m++) {
					ankerl::nanobench::doNotOptimizeAway(arr[i][j][k][m]);
					arr[i][j][k][m] = 0xcafebabe;
				}
			}
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

void BM_nonstd_seqwr_4d() {
	nstd::ndarray<int, 16, 16, 16, 16> arr;
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				for (int m = 0; m < 16; m++) {
					ankerl::nanobench::doNotOptimizeAway(arr[i][j][k][m]);
					arr[i][j][k][m] = 0xcafebabe;
				}
			}
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

TEST_CASE("bench_seqwr_4d") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_seqwr_4d")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("plain / seqwr_4d", BM_plain_seqwr_4d);
	bench.run("nonstd / seqwr_4d", BM_nonstd_seqwr_4d);
}
// bench_seqwr_4d ENDS

// bench_rndwr_1d BEGINS
void BM_plain_rndwr_1d() {
	int arr[16384]{};
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 16384; i++) {
		int idx = rng.bounded(16384);
		ankerl::nanobench::doNotOptimizeAway(arr[idx]);
		arr[idx] = 0xcafebabe;
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

void BM_nonstd_rndwr_1d() {
	nstd::ndarray<int, 16384> arr;
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 16384; i++) {
		int idx = rng.bounded(16384);
		ankerl::nanobench::doNotOptimizeAway(arr[idx]);
		arr[idx] = 0xcafebabe;
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

TEST_CASE("bench_rndwr_1d") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_rndwr_1d")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("plain / rndwr_1d", BM_plain_rndwr_1d);
	bench.run("nonstd / rndwr_1d", BM_nonstd_rndwr_1d);
}
// bench_rndwr_1d ENDS

// bench_rndwr_2d BEGINS
void BM_plain_rndwr_2d() {
	int arr[128][128]{};
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			int idx1 = rng.bounded(128), idx2 = rng.bounded(128);
			ankerl::nanobench::doNotOptimizeAway(arr[idx1][idx2]);
			arr[idx1][idx2] = 0xcafebabe;
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

void BM_nonstd_rndwr_2d() {
	nstd::ndarray<int, 128, 128> arr;
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			int idx1 = rng.bounded(128), idx2 = rng.bounded(128);
			ankerl::nanobench::doNotOptimizeAway(arr[idx1][idx2]);
			arr[idx1][idx2] = 0xcafebabe;
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

TEST_CASE("bench_rndwr_2d") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_rndwr_2d")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("plain / rndwr_2d", BM_plain_rndwr_2d);
	bench.run("nonstd / rndwr_2d", BM_nonstd_rndwr_2d);
}
// bench_rndwr_2d ENDS

// bench_rndwr_3d BEGINS
void BM_plain_rndwr_3d() {
	int arr[32][32][32]{};
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			for (int k = 0; k < 32; k++) {
				int idx1 = rng.bounded(32);
				int idx2 = rng.bounded(32);
				int idx3 = rng.bounded(32);
				ankerl::nanobench::doNotOptimizeAway(arr[idx1][idx2][idx3]);
				arr[idx1][idx2][idx3] = 0xcafebabe;
			}
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

void BM_nonstd_rndwr_3d() {
	nstd::ndarray<int, 32, 32, 32> arr;
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			for (int k = 0; k < 32; k++) {
				int idx1 = rng.bounded(32);
				int idx2 = rng.bounded(32);
				int idx3 = rng.bounded(32);
				ankerl::nanobench::doNotOptimizeAway(arr[idx1][idx2][idx3]);
				arr[idx1][idx2][idx3] = 0xcafebabe;
			}
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

TEST_CASE("bench_rndwr_3d") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_rndwr_3d")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("plain / rndwr_3d", BM_plain_rndwr_3d);
	bench.run("nonstd / rndwr_3d", BM_nonstd_rndwr_3d);
}
// bench_rndwr_3d ENDS

// bench_rndwr_4d BEGINS
void BM_plain_rndwr_4d() {
	int arr[16][16][16][16]{};
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				for (int m = 0; m < 16; m++) {
					int idx1 = rng.bounded(16);
					int idx2 = rng.bounded(16);
					int idx3 = rng.bounded(16);
					int idx4 = rng.bounded(16);
					ankerl::nanobench::doNotOptimizeAway(arr[idx1][idx2][idx3][idx4]);
					arr[idx1][idx2][idx3][idx4] = 0xcafebabe;
				}
			}
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

void BM_nonstd_rndwr_4d() {
	nstd::ndarray<int, 16, 16, 16, 16> arr;
	ankerl::nanobench::doNotOptimizeAway(arr);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				for (int m = 0; m < 16; m++) {
					int idx1 = rng.bounded(16);
					int idx2 = rng.bounded(16);
					int idx3 = rng.bounded(16);
					int idx4 = rng.bounded(16);
					ankerl::nanobench::doNotOptimizeAway(arr[idx1][idx2][idx3][idx4]);
					arr[idx1][idx2][idx3][idx4] = 0xcafebabe;
				}
			}
		}
	}
	ankerl::nanobench::doNotOptimizeAway(arr);
}

TEST_CASE("bench_rndwr_4d") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_rndwr_4d")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("plain / rndwr_4d", BM_plain_rndwr_4d);
	bench.run("nonstd / rndwr_4d", BM_nonstd_rndwr_4d);
}
// bench_rndwr_4d ENDS

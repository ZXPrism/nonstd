#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include <math/nstd_math.h>
#include <cmath>

// bench_abs BEGINS
void BM_nonstd_abs() {
	int x = -1;
	auto res = nstd::abs(x);
	ankerl::nanobench::doNotOptimizeAway(res);
}

void BM_std_abs() {
	int x = -1;
	auto res = std::abs(x);
	ankerl::nanobench::doNotOptimizeAway(res);
}

TEST_CASE("bench_abs") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_abs")
	    .warmup(100)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("std / abs", BM_std_abs);
	bench.run("nonstd / abs", BM_nonstd_abs);
}
// bench_abs ENDS

// bench_max BEGINS
void BM_nonstd_max() {
	int x = 123, y = 456;
	auto res = nstd::max(x, y);
	ankerl::nanobench::doNotOptimizeAway(res);
}

void BM_std_max() {
	int x = 123, y = 456;
	auto res = std::max(x, y);
	ankerl::nanobench::doNotOptimizeAway(res);
}

TEST_CASE("bench_max") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_max")
	    .warmup(100)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("std / max", BM_std_max);
	bench.run("nonstd / max", BM_nonstd_max);
}
// bench_max ENDS

// bench_min BEGINS
void BM_nonstd_min() {
	int x = 123, y = 456;
	auto res = nstd::min(x, y);
	ankerl::nanobench::doNotOptimizeAway(res);
}

void BM_std_min() {
	int x = 123, y = 456;
	auto res = std::min(x, y);
	ankerl::nanobench::doNotOptimizeAway(res);
}

TEST_CASE("bench_min") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_min")
	    .warmup(100)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("std / min", BM_std_min);
	bench.run("nonstd / min", BM_nonstd_min);
}
// bench_min ENDS

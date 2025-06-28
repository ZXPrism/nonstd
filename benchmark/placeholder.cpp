#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

int add(int a, int b) {
	return a + b;
}

int mul(int a, int b) {
	return a * b;
}

int main() {
	ankerl::nanobench::Bench bench;
	bench.title("Bench Placeholder");

	int a = 114, b = 514;

	bench.run("add", [&] {
		ankerl::nanobench::doNotOptimizeAway(add(a, b));
	});

	bench.run("mul", [&] {
		ankerl::nanobench::doNotOptimizeAway(mul(a, b));
	});

	return 0;
}

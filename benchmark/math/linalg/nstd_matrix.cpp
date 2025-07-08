#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include <math/linalg/nstd_vector.h>

#include <glm/glm.hpp>
#include <Eigen/Dense>

// bench_matrix_add BEGINS
void BM_nonstd_matrix_add() {
	nstd::linalg::matrix2f mat2f_a(1.0f, 2.0f, 3.0f, 4.0f), mat2f_b(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(mat2f_a + mat2f_b);
}

void BM_eigen_matrix_add() {
	Eigen::Matrix2f mat2f_a, mat2f_b;
	mat2f_a << 1.0f, 2.0f, 3.0f, 4.0f;
	mat2f_b << 1.0f, 2.0f, 3.0f, 4.0f;
	ankerl::nanobench::doNotOptimizeAway((mat2f_a + mat2f_b).eval());
}

void BM_glm_matrix_add() {
	glm::mat2 mat2f_a(1.0f, 2.0f, 3.0f, 4.0f), mat2f_b(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(mat2f_a + mat2f_b);
}

TEST_CASE("bench_matrix_add") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_matrix_add")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("eigen / matrix_add", BM_eigen_matrix_add);
	bench.run("glm / matrix_add", BM_glm_matrix_add);
	bench.run("nonstd / matrix_add", BM_nonstd_matrix_add);
}
// bench_matrix_add ENDS

// bench_matrix_add_multiple BEGINS
void BM_nonstd_matrix_add_multiple() {
	nstd::linalg::matrix2f mat2f_a(1.0f, 2.0f, 3.0f, 4.0f), mat2f_b(1.0f, 2.0f, 3.0f, 4.0f);
	nstd::linalg::matrix2f mat2f_c(1.0f, 2.0f, 3.0f, 4.0f), mat2f_d(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(mat2f_a + mat2f_b + mat2f_c + mat2f_d);
}

void BM_eigen_matrix_add_multiple() {
	Eigen::Matrix2f mat2f_a, mat2f_b, mat2f_c, mat2f_d;
	mat2f_a << 1.0f, 2.0f, 3.0f, 4.0f;
	mat2f_b << 1.0f, 2.0f, 3.0f, 4.0f;
	mat2f_c << 1.0f, 2.0f, 3.0f, 4.0f;
	mat2f_d << 1.0f, 2.0f, 3.0f, 4.0f;
	ankerl::nanobench::doNotOptimizeAway((mat2f_a + mat2f_b + mat2f_c + mat2f_d).eval());
}

void BM_glm_matrix_add_multiple() {
	glm::mat2 mat2f_a(1.0f, 2.0f, 3.0f, 4.0f), mat2f_b(1.0f, 2.0f, 3.0f, 4.0f);
	glm::mat2 mat2f_c(1.0f, 2.0f, 3.0f, 4.0f), mat2f_d(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(mat2f_a + mat2f_b + mat2f_c + mat2f_d);
}

TEST_CASE("bench_matrix_add_multiple") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_matrix_add_multiple")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("eigen / matrix_add_multiple", BM_eigen_matrix_add_multiple);
	bench.run("glm / matrix_add_multiple", BM_glm_matrix_add_multiple);
	bench.run("nonstd / matrix_add_multiple", BM_nonstd_matrix_add_multiple);
}
// bench_matrix_add_multiple ENDS

// bench_matrix_mul BEGINS
void BM_nonstd_matrix_mul() {
	nstd::linalg::matrix4f mat4f_a, mat4f_b;
	ankerl::nanobench::doNotOptimizeAway(mat4f_a * mat4f_b);
}

void BM_eigen_matrix_mul() {
	Eigen::Matrix4f mat4f_a, mat4f_b;
	ankerl::nanobench::doNotOptimizeAway((mat4f_a * mat4f_b).eval());
}

void BM_glm_matrix_mul() {
	glm::mat4 mat4f_a, mat4f_b;
	ankerl::nanobench::doNotOptimizeAway(mat4f_a * mat4f_b);
}

TEST_CASE("bench_matrix_mul") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_matrix_mul")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("eigen / matrix_mul", BM_eigen_matrix_mul);
	bench.run("glm / matrix_mul", BM_glm_matrix_mul);
	bench.run("nonstd / matrix_mul", BM_nonstd_matrix_mul);
}
// bench_matrix_mul ENDS

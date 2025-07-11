#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include <math/linalg/nstd_vector.h>

#include <glm/glm.hpp>
#include <Eigen/Dense>

// bench_vector_normalize BEGINS
void BM_nonstd_vector_normalize() {
	nstd::linalg::vector4f vec4f(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(vec4f.normalized());
}

void BM_eigen_vector_normalize() {
	Eigen::Vector4f vec4f(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(vec4f.normalized());
}

void BM_glm_vector_normalize() {
	glm::vec4 vec4f(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(glm::normalize(vec4f));
}

TEST_CASE("bench_vector_normalize") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_vector_normalize")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("eigen / vector_normalize", BM_eigen_vector_normalize);
	bench.run("glm / vector_normalize", BM_glm_vector_normalize);
	bench.run("nonstd / vector_normalize", BM_nonstd_vector_normalize);
}
// bench_vector_normalize ENDS

// bench_vector_norm_squared BEGINS
void BM_nonstd_vector_norm_squared() {
	nstd::linalg::vector4f vec4f(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(vec4f.norm_squared());
}

void BM_eigen_vector_norm_squared() {
	Eigen::Vector4f vec4f(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(vec4f.squaredNorm());
}

void BM_glm_vector_norm_squared() {
	glm::vec4 vec4f(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(glm::dot(vec4f, vec4f));
}

TEST_CASE("bench_vector_norm_squared") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_vector_norm_squared")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("eigen / vector_norm_squared", BM_eigen_vector_norm_squared);
	bench.run("glm / vector_norm_squared", BM_glm_vector_norm_squared);
	bench.run("nonstd / vector_norm_squared", BM_nonstd_vector_norm_squared);
}
// bench_vector_norm_squared ENDS

// bench_vector_add BEGINS
void BM_nonstd_vector_add() {
	nstd::linalg::vector4f vec4f_a(1.0f, 2.0f, 3.0f, 4.0f), vec4f_b(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(vec4f_a + vec4f_b);
}

void BM_eigen_vector_add() {
	Eigen::Vector4f vec4f_a(1.0f, 2.0f, 3.0f, 4.0f), vec4f_b(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway((vec4f_a + vec4f_b).eval());
}

void BM_glm_vector_add() {
	glm::vec4 vec4f_a(1.0f, 2.0f, 3.0f, 4.0f), vec4f_b(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(vec4f_a + vec4f_b);
}

TEST_CASE("bench_vector_add") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_vector_add")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("eigen / vector_add", BM_eigen_vector_add);
	bench.run("glm / vector_add", BM_glm_vector_add);
	bench.run("nonstd / vector_add", BM_nonstd_vector_add);
}
// bench_vector_add ENDS

// bench_vector_add_multiple BEGINS
void BM_nonstd_vector_add_multiple() {
	nstd::linalg::vector4f vec4f_a(1.0f, 2.0f, 3.0f, 4.0f), vec4f_b(1.0f, 2.0f, 3.0f, 4.0f);
	nstd::linalg::vector4f vec4f_c(1.0f, 2.0f, 3.0f, 4.0f), vec4f_d(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(vec4f_a + vec4f_b + vec4f_c + vec4f_d);
}

void BM_eigen_vector_add_multiple() {
	Eigen::Vector4f vec4f_a(1.0f, 2.0f, 3.0f, 4.0f), vec4f_b(1.0f, 2.0f, 3.0f, 4.0f);
	Eigen::Vector4f vec4f_c(1.0f, 2.0f, 3.0f, 4.0f), vec4f_d(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway((vec4f_a + vec4f_b + vec4f_c + vec4f_d).eval());
	// NOTE(25/07/08): remove eval(), it's 6x slower!
	// why? an un-evaled expr template is slower than eval-ed ver?
	// may because, if we access to un-evaled one, each time we need to re-trigger calculation
}

void BM_glm_vector_add_multiple() {
	glm::vec4 vec4f_a(1.0f, 2.0f, 3.0f, 4.0f), vec4f_b(1.0f, 2.0f, 3.0f, 4.0f);
	glm::vec4 vec4f_c(1.0f, 2.0f, 3.0f, 4.0f), vec4f_d(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(vec4f_a + vec4f_b + vec4f_c + vec4f_d);
}

TEST_CASE("bench_vector_add_multiple") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_vector_add_multiple")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("eigen / vector_add_multiple", BM_eigen_vector_add_multiple);
	bench.run("glm / vector_add_multiple", BM_glm_vector_add_multiple);
	bench.run("nonstd / vector_add_multiple", BM_nonstd_vector_add_multiple);
}
// bench_vector_add_multiple ENDS

// bench_vector_dot BEGINS
void BM_nonstd_vector_dot() {
	nstd::linalg::vector4f vec4f_a(1.0f, 2.0f, 3.0f, 4.0f), vec4f_b(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(nstd::linalg::dot(vec4f_a, vec4f_b));
}

void BM_eigen_vector_dot() {
	Eigen::Vector4f vec4f_a(1.0f, 2.0f, 3.0f, 4.0f), vec4f_b(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(vec4f_a.dot(vec4f_b));
}

void BM_glm_vector_dot() {
	glm::vec4 vec4f_a(1.0f, 2.0f, 3.0f, 4.0f), vec4f_b(1.0f, 2.0f, 3.0f, 4.0f);
	ankerl::nanobench::doNotOptimizeAway(glm::dot(vec4f_a, vec4f_b));
}

TEST_CASE("bench_vector_dot") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_vector_dot")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("eigen / vector_dot", BM_eigen_vector_dot);
	bench.run("glm / vector_dot", BM_glm_vector_dot);
	bench.run("nonstd / vector_dot", BM_nonstd_vector_dot);
}
// bench_vector_dot ENDS

// bench_vector_cross BEGINS
void BM_nonstd_vector_cross() {
	nstd::linalg::vector3f vec3f_a(1.0f, 2.0f, 3.0f), vec3f_b(1.0f, 2.0f, 3.0f);
	ankerl::nanobench::doNotOptimizeAway(nstd::linalg::cross(vec3f_a, vec3f_b));
}

void BM_eigen_vector_cross() {
	Eigen::Vector3f vec3f_a(1.0f, 2.0f, 3.0f), vec3f_b(1.0f, 2.0f, 3.0f);
	ankerl::nanobench::doNotOptimizeAway(vec3f_a.cross(vec3f_b));
}

void BM_glm_vector_cross() {
	glm::vec3 vec3f_a(1.0f, 2.0f, 3.0f), vec3f_b(1.0f, 2.0f, 3.0f);
	ankerl::nanobench::doNotOptimizeAway(glm::cross(vec3f_a, vec3f_b));
}

TEST_CASE("bench_vector_cross") {
	auto bench = ankerl::nanobench::Bench();
	bench.title("bench_vector_cross")
	    .warmup(100)
	    .minEpochIterations(1000)
	    .performanceCounters(true)
	    .relative(true);

	bench.run("eigen / vector_cross", BM_eigen_vector_cross);
	bench.run("glm / vector_cross", BM_glm_vector_cross);
	bench.run("nonstd / vector_cross", BM_nonstd_vector_cross);
}
// bench_vector_cross ENDS

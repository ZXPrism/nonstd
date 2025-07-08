#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <math/linalg/nstd_matrix.h>
#include <math/linalg/nstd_vector.h>
#include <math/nstd_math.h>
#include <util/nstd_type_traits.h>
#include <util/nstd_utility.h>

#include <Eigen/Dense>

// TODO: REMOVE these deps in future versions
#include <random>

float random_float(float left, float right) {
	static std::random_device rd;
	static std::mt19937_64 engine(rd());
	std::uniform_real_distribution<float> dist(left, right);
	return dist(engine);
}

template<typename Mat, typename Ty = Mat::value_type>
    requires(nstd::remove_cvref_t<Mat>::size_row() == 2 &&
             nstd::remove_cvref_t<Mat>::size_col() == 2)
constexpr bool check_matrix2(Mat &&mat, Ty &&a11, Ty &&a12, Ty &&a21, Ty &&a22) {
	return nstd::is_approx(mat[0][0], a11, 1e-5f) &&
	       nstd::is_approx(mat[0][1], a12, 1e-5f) &&
	       nstd::is_approx(mat[1][0], a21, 1e-5f) &&
	       nstd::is_approx(mat[1][1], a22, 1e-5f);
}

TEST_CASE("size") {
	CHECK(nstd::linalg::matrix<int, 3, 4, true>::size_row() == 3);
	CHECK(nstd::linalg::matrix<int, 3, 4, true>::size_col() == 4);
}

TEST_CASE("init / diagonal init") {
	constexpr nstd::linalg::matrix2f mat2f(123.0f);

	CHECK(check_matrix2(mat2f, 123.0f, 0.0f, 0.0f, 123.0f));
}

TEST_CASE("init / variadic") {
	constexpr nstd::linalg::matrix2f mat2f(123.0f, 456.0f, 678.0f, 91011.0f);

	CHECK(check_matrix2(mat2f, 123.0f, 456.0f, 678.0f, 91011.0f));
}

TEST_CASE("util / zeros") {
	constexpr auto mat2f = nstd::linalg::matrix2f::zeros();

	CHECK(check_matrix2(mat2f, 0.0f, 0.0f, 0.0f, 0.0f));
}

TEST_CASE("util / ones") {
	constexpr auto mat2f = nstd::linalg::matrix2f::ones();

	CHECK(check_matrix2(mat2f, 1.0f, 1.0f, 1.0f, 1.0f));
}

TEST_CASE("util / identity") {
	constexpr auto mat2f = nstd::linalg::matrix2f::identity();

	CHECK(check_matrix2(mat2f, 1.0f, 0.0f, 0.0f, 1.0f));
}

TEST_CASE("mat mul 1") {
	float a11 = random_float(-100.0f, 100.0f);
	float a12 = random_float(-100.0f, 100.0f);
	float a21 = random_float(-100.0f, 100.0f);
	float a22 = random_float(-100.0f, 100.0f);

	nstd::linalg::matrix2f mat2f_a(a11, a12, a21, a22);
	Eigen::Matrix2f eigen_mat2f_a;
	eigen_mat2f_a << a11, a12, a21, a22;

	float a11_ = random_float(-100.0f, 100.0f);
	float a12_ = random_float(-100.0f, 100.0f);
	float a21_ = random_float(-100.0f, 100.0f);
	float a22_ = random_float(-100.0f, 100.0f);

	nstd::linalg::matrix2f mat2f_b(a11_, a12_, a21_, a22_);
	Eigen::Matrix2f eigen_mat2f_b;
	eigen_mat2f_b << a11_, a12_, a21_, a22_;

	auto mul_a = mat2f_a * mat2f_b;
	auto mul_b = (eigen_mat2f_a * eigen_mat2f_b).eval();

	CHECK(check_matrix2(mul_a, mul_b(0, 0), mul_b(0, 1), mul_b(1, 0), mul_b(1, 1)));
}

TEST_CASE("mat mul 2") {
	float a11 = random_float(-100.0f, 100.0f);
	float a12 = random_float(-100.0f, 100.0f);
	float a13 = random_float(-100.0f, 100.0f);
	float a21 = random_float(-100.0f, 100.0f);
	float a22 = random_float(-100.0f, 100.0f);
	float a23 = random_float(-100.0f, 100.0f);

	nstd::linalg::matrix<float, 2, 3, false> mat2f_a(a11, a12, a13, a21, a22, a23);
	Eigen::Matrix<float, 2, 3> eigen_mat2f_a;
	eigen_mat2f_a << a11, a12, a13, a21, a22, a23;

	float a11_ = random_float(-100.0f, 100.0f);
	float a12_ = random_float(-100.0f, 100.0f);
	float a13_ = random_float(-100.0f, 100.0f);
	float a21_ = random_float(-100.0f, 100.0f);
	float a22_ = random_float(-100.0f, 100.0f);
	float a23_ = random_float(-100.0f, 100.0f);

	nstd::linalg::matrix<float, 3, 2, false> mat2f_b(a11_, a12_, a13_, a21_, a22_, a23_);
	Eigen::Matrix<float, 3, 2> eigen_mat2f_b;
	eigen_mat2f_b << a11_, a12_, a13_, a21_, a22_, a23_;

	auto mul_a = mat2f_a * mat2f_b;
	auto mul_b = (eigen_mat2f_a * eigen_mat2f_b).eval();

	CHECK(check_matrix2(mul_a, mul_b(0, 0), mul_b(0, 1), mul_b(1, 0), mul_b(1, 1)));
}

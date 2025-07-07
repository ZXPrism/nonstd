#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <math/linalg/nstd_vector.h>
#include <math/nstd_math.h>
#include <util/nstd_type_traits.h>
#include <util/nstd_utility.h>

#include <Eigen/Dense>

// TODO: REMOVE these deps in future versions
#include <random>
#include <utility>

float random_float(float left, float right) {
	static std::random_device rd;
	static std::mt19937_64 engine(rd());
	std::uniform_real_distribution<float> dist(left, right);
	return dist(engine);
}

template<typename Vec, typename... Args, std::size_t... Index>
constexpr bool check_vector_impl(Vec &&vec, const std::tuple<Args...> &arg_tuple, std::index_sequence<Index...>) {
	return ((nstd::is_approx(vec[Index],
	                         std::get<Index>(arg_tuple),
	                         static_cast<typename nstd::remove_cvref_t<Vec>::value_type>(1e-5))) &&
	        ...);
}

template<typename Vec, typename... Args>
constexpr bool check_vector(Vec &&vec, Args &&...args) {
	static_assert(nstd::remove_cvref_t<Vec>::size_row() == sizeof...(Args) &&
	              nstd::remove_cvref_t<Vec>::size_col() == 1);
	auto arg_tuple = std::forward_as_tuple(args...);
	return check_vector_impl(nstd::forward<Vec>(vec), arg_tuple, std::make_index_sequence<sizeof...(Args)>{});
}

TEST_CASE("size") {
	CHECK(nstd::linalg::vector2f::size_row() == 2);
	CHECK(nstd::linalg::vector3d::size_row() == 3);
}

TEST_CASE("init / single val") {
	constexpr nstd::linalg::vector2f vec2f(0.0f);
	CHECK(check_vector(vec2f, 0.0f, 0.0f));
	CHECK(!check_vector(vec2f, 0.0f, 1.0f));
}

TEST_CASE("init / variadic") {
	constexpr nstd::linalg::vector2f vec2f(123.0f, 456.0f);
	constexpr nstd::linalg::vector4f vec4f(123.0f, 456.0f, 678.0f, 91011.0f);

	CHECK(check_vector(vec2f, 123.0f, 456.0f));
	CHECK(!check_vector(vec2f, 623.0f, 456.0f));
	CHECK(check_vector(vec4f, 123.0f, 456.0f, 678.0f, 91011.0f));
}

TEST_CASE("init / initializer_list") {
	constexpr nstd::linalg::vector2f vec2f{ 123.0f, 456.0f };
	constexpr nstd::linalg::vector4f vec4f{ 123.0f, 456.0f, 678.0f, 91011.0f };

	CHECK(check_vector(vec2f, 123.0f, 456.0f));
	CHECK(!check_vector(vec2f, 623.0f, 456.0f));
	CHECK(check_vector(vec4f, 123.0f, 456.0f, 678.0f, 91011.0f));
}

TEST_CASE("norm & norm_squared") {
	float x = random_float(-100.0f, 100.0f);
	float y = random_float(-100.0f, 100.0f);
	float z = random_float(-100.0f, 100.0f);
	float w = random_float(-100.0f, 100.0f);

	nstd::linalg::vector4f vec4f(x, y, z, w);
	Eigen::Vector4f eigen_vec4f(x, y, z, w);

	CHECK(nstd::is_approx(vec4f.norm(), eigen_vec4f.norm(), 1e-5f));
	CHECK(nstd::is_approx(vec4f.norm_squared(), eigen_vec4f.squaredNorm(), 1e-5f));
}

TEST_CASE("normalize & normalized") {
	float x = random_float(-100.0f, 100.0f);
	float y = random_float(-100.0f, 100.0f);
	float z = random_float(-100.0f, 100.0f);
	float w = random_float(-100.0f, 100.0f);

	nstd::linalg::vector4f vec4f(x, y, z, w);
	Eigen::Vector4f eigen_vec4f(x, y, z, w);
	eigen_vec4f.normalize();

	auto norm_vec4f = vec4f.normalized();
	CHECK(check_vector(norm_vec4f, eigen_vec4f[0], eigen_vec4f[1], eigen_vec4f[2], eigen_vec4f[3]));

	vec4f.normalize();
	CHECK(check_vector(vec4f, eigen_vec4f[0], eigen_vec4f[1], eigen_vec4f[2], eigen_vec4f[3]));

	nstd::linalg::vector4f zero_vec(0.0f);
	zero_vec.normalize();
	CHECK(check_vector(zero_vec, 0.0f, 0.0f, 0.0f, 0.0f));
}

TEST_CASE("dot") {
	float x = random_float(-100.0f, 100.0f);
	float y = random_float(-100.0f, 100.0f);
	float z = random_float(-100.0f, 100.0f);
	float w = random_float(-100.0f, 100.0f);

	nstd::linalg::vector4f vec4f_a(x, y, z, w);
	Eigen::Vector4f eigen_vec4f_a(x, y, z, w);

	float x1 = random_float(-100.0f, 100.0f);
	float y1 = random_float(-100.0f, 100.0f);
	float z1 = random_float(-100.0f, 100.0f);
	float w1 = random_float(-100.0f, 100.0f);

	nstd::linalg::vector4f vec4f_b(x1, y1, z1, w1);
	Eigen::Vector4f eigen_vec4f_b(x1, y1, z1, w1);

	CHECK(nstd::is_approx(nstd::linalg::dot(vec4f_a, vec4f_b), eigen_vec4f_a.dot(eigen_vec4f_b), 1e-5f));
}

TEST_CASE("cross") {
	float x = random_float(-100.0f, 100.0f);
	float y = random_float(-100.0f, 100.0f);
	float z = random_float(-100.0f, 100.0f);

	nstd::linalg::vector3f vec3f_a(x, y, z);
	Eigen::Vector3f eigen_vec3f_a(x, y, z);

	float x1 = random_float(-100.0f, 100.0f);
	float y1 = random_float(-100.0f, 100.0f);
	float z1 = random_float(-100.0f, 100.0f);

	nstd::linalg::vector3f vec3f_b(x1, y1, z1);
	Eigen::Vector3f eigen_vec3f_b(x1, y1, z1);

	auto cross_a = nstd::linalg::cross(vec3f_a, vec3f_b);
	auto cross_b = eigen_vec3f_a.cross(eigen_vec3f_b);

	CHECK(check_vector(cross_a, cross_b[0], cross_b[1], cross_b[2]));
}

TEST_CASE("add") {
	float x = random_float(-100.0f, 100.0f);
	float y = random_float(-100.0f, 100.0f);
	float z = random_float(-100.0f, 100.0f);

	nstd::linalg::vector3f vec3f_a(x, y, z);
	Eigen::Vector3f eigen_vec3f_a(x, y, z);

	float x1 = random_float(-100.0f, 100.0f);
	float y1 = random_float(-100.0f, 100.0f);
	float z1 = random_float(-100.0f, 100.0f);

	nstd::linalg::vector3f vec3f_b(x1, y1, z1);
	Eigen::Vector3f eigen_vec3f_b(x1, y1, z1);

	auto add_a = vec3f_a + vec3f_b;
	auto add_b = eigen_vec3f_a + eigen_vec3f_b;

	CHECK(check_vector(add_a, add_b[0], add_b[1], add_b[2]));
}

TEST_CASE("sub") {
	float x = random_float(-100.0f, 100.0f);
	float y = random_float(-100.0f, 100.0f);
	float z = random_float(-100.0f, 100.0f);

	nstd::linalg::vector3f vec3f_a(x, y, z);
	Eigen::Vector3f eigen_vec3f_a(x, y, z);

	float x1 = random_float(-100.0f, 100.0f);
	float y1 = random_float(-100.0f, 100.0f);
	float z1 = random_float(-100.0f, 100.0f);

	nstd::linalg::vector3f vec3f_b(x1, y1, z1);
	Eigen::Vector3f eigen_vec3f_b(x1, y1, z1);

	auto add_a = vec3f_a - vec3f_b;
	auto add_b = eigen_vec3f_a - eigen_vec3f_b;

	CHECK(check_vector(add_a, add_b[0], add_b[1], add_b[2]));
}

TEST_CASE("scalar") {
	float x = random_float(-100.0f, 100.0f);
	float y = random_float(-100.0f, 100.0f);
	float z = random_float(-100.0f, 100.0f);
	float w = random_float(-100.0f, 100.0f);
	float scalar = random_float(-100.0f, 100.0f);

	nstd::linalg::vector4f vec4f(x, y, z, w);
	Eigen::Vector4f eigen_vec4f(x, y, z, w);

	auto s_vec = scalar * vec4f;
	auto vec_s = vec4f * scalar;
	auto eigen_s_vec = scalar * eigen_vec4f;
	auto eigen_vec_s = eigen_vec4f * scalar;

	CHECK(check_vector(s_vec, vec_s[0], vec_s[1], vec_s[2], vec_s[3]));
	CHECK(check_vector(s_vec, eigen_vec_s[0], eigen_vec_s[1], eigen_vec_s[2], eigen_vec_s[3]));
	CHECK(check_vector(s_vec, eigen_s_vec[0], eigen_s_vec[1], eigen_s_vec[2], eigen_s_vec[3]));
}

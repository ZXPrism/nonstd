#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <math/linalg/nstd_vector.h>
#include <util/nstd_type_traits.h>
#include <util/nstd_utility.h>

#include <Eigen/Dense>

// TODO: REMOVE this dep in future versions
#include <utility>

template<typename Vec, typename... Args, std::size_t... Index>
constexpr bool check_vector_impl(Vec &&vec, const std::tuple<Args...> &arg_tuple, std::index_sequence<Index...>) {
	return ((vec[Index] == std::get<Index>(arg_tuple)) && ...);
}

template<typename Vec, typename... Args>
constexpr bool check_vector(Vec &&vec, Args &&...args) {
	static_assert(nstd::remove_cvref_t<Vec>::size() == sizeof...(Args));
	auto arg_tuple = std::forward_as_tuple(args...);
	return check_vector_impl(nstd::forward<Vec>(vec), arg_tuple, std::make_index_sequence<sizeof...(Args)>{});
}

TEST_CASE("size") {
	CHECK(nstd::linalg::vector2f::size() == 2);
	CHECK(nstd::linalg::vector3d::size() == 3);
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

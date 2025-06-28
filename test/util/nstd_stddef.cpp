#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <util/nstd_stddef.h>

#include <cstddef>
#include <type_traits>

TEST_CASE("baseline") {
	CHECK(std::is_same_v<nstd::size_t, std::size_t>);
	CHECK(std::is_same_v<nstd::ptrdiff_t, std::ptrdiff_t>);
	CHECK(std::is_same_v<nstd::nullptr_t, std::nullptr_t>);
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <util/nstd_type_traits.h>

TEST_CASE("integral_constant::basic") {
	nstd::integral_constant<int, 123> x;
	nstd::integral_constant<int, 456> y;

	CHECK_EQ(x.value, 123);
	CHECK_EQ(x(), 123);
	CHECK_EQ(x + y, 123 + 456);
	CHECK_EQ(x + 1, 124);
	CHECK_EQ(nstd::true_type(), true);
	CHECK_EQ(nstd::false_type::value, false);
}

TEST_CASE("integral_constant::enum") {
	enum class E {
		e1,
		e2
	};
	using intcons1 = nstd::integral_constant<E, E::e1>;
	using intcons2 = nstd::integral_constant<E, E::e2>;

	CHECK_EQ(intcons1(), E::e1);
	CHECK_EQ(intcons2::value, E::e2);
	CHECK_NE(intcons1(), intcons2());
}

TEST_CASE("is_same") {
	CHECK(nstd::is_same<int, int>::value);
	CHECK(nstd::is_same_v<int, int>);
	CHECK(!nstd::is_same_v<int, bool>);
	CHECK(!nstd::is_same_v<const char *, decltype("hello")>);

	// NOTE: char is neither signed char nor unsigned char
	// it's undefined in standard
	// most compilers use signed char in essence
	// but some compilers use unsigned char
	CHECK(!nstd::is_same_v<char, signed char>);

	CHECK(nstd::is_same_v<int, signed int>);
}

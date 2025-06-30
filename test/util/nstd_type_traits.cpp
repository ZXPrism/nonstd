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

	struct A {
		int a;
		void b();
		void c();
	};

	// NOTE: pointer to member functions are special
	// they're not real pointers!
	// but can be accessed using operator.* or operator->*
	CHECK(nstd::is_same_v<void (A::*)(), decltype(&A::b)>);
	CHECK(nstd::is_same_v<decltype(&A::b), decltype(&A::c)>);
}

TEST_CASE("conditional") {
	CHECK(nstd::is_same_v<nstd::conditional<true, int, float>::type, int>);
	CHECK(nstd::is_same_v<nstd::conditional_t<true, int, float>, int>);
	CHECK(nstd::is_same_v<nstd::conditional_t<false, int, float>, float>);
}

TEST_CASE("is_const") {
	CHECK(!nstd::is_const<int>::value);
	CHECK(!nstd::is_const_v<bool>);
	CHECK(nstd::is_const_v<const int>);
	CHECK(!nstd::is_const_v<const char *>);
	CHECK(nstd::is_const_v<const char *const>);
	CHECK(nstd::is_const_v<char *const>);
	CHECK(!nstd::is_const_v<const float &>);
}

TEST_CASE("is_volatile") {
	CHECK(!nstd::is_volatile<int>::value);
	CHECK(!nstd::is_volatile_v<bool>);
	CHECK(nstd::is_volatile_v<volatile int>);
}

TEST_CASE("remove_const") {
	CHECK(!nstd::is_const_v<nstd::remove_const<const int>::type>);
	CHECK(!nstd::is_const_v<nstd::remove_const_t<const float>>);
	CHECK(!nstd::is_same_v<nstd::remove_const_t<const char *>, char *>);
	CHECK(nstd::is_same_v<nstd::remove_const_t<char *const>, char *>);
	CHECK(nstd::is_same_v<nstd::remove_const_t<const char &>, const char &>);
}

TEST_CASE("remove_volatile") {
	CHECK(!nstd::is_volatile_v<nstd::remove_volatile<volatile int>::type>);
	CHECK(nstd::is_same_v<nstd::remove_volatile_t<volatile double>, double>);
}

TEST_CASE("remove_cv") {
	CHECK(!nstd::is_volatile_v<nstd::remove_cv<volatile int>::type>);
	CHECK(nstd::is_same_v<nstd::remove_cv_t<const volatile double>, double>);
	CHECK(nstd::is_same_v<nstd::remove_cv_t<const float>, float>);
	CHECK(nstd::is_same_v<nstd::remove_cv_t<volatile unsigned>, unsigned>);
}

TEST_CASE("add_const & add_volatile & add_cv") {
	struct foo {
		int m() && { return 0; }
		int m() const && { return 1; }
		int m() volatile && { return 2; }
		int m() const volatile && { return 3; }
	};

	CHECK_EQ(foo{}.m(), 0);
	CHECK_EQ(nstd::add_const_t<foo>{}.m(), 1);
	CHECK_EQ(nstd::add_volatile_t<foo>{}.m(), 2);
	CHECK_EQ(nstd::add_cv_t<foo>{}.m(), 3);
}

TEST_CASE("remove_reference") {
	CHECK(nstd::is_same_v<nstd::remove_reference_t<int>, int>);
	CHECK(nstd::is_same_v<nstd::remove_reference_t<char &>, char>);
	CHECK(nstd::is_same_v<nstd::remove_reference_t<float &&>, float>);
	CHECK(nstd::is_same_v<nstd::remove_reference_t<const double &&>, const double>);
}

TEST_CASE("is_array") {
	CHECK(!nstd::is_array_v<int>);
	CHECK(nstd::is_array_v<float[]>);
	CHECK(nstd::is_array_v<double[123]>);

	class A {};
	CHECK(!nstd::is_array_v<A>);
	CHECK(nstd::is_array_v<A[]>);
	CHECK(nstd::is_array_v<A[123]>);
}

TEST_CASE("is_reference") {
	CHECK(!nstd::is_reference_v<int>);
	CHECK(nstd::is_reference_v<int &>);
	CHECK(nstd::is_reference_v<const int &>);
	CHECK(!nstd::is_reference_v<int *>);
	CHECK(nstd::is_reference_v<int *******&>);
	CHECK(nstd::is_reference_v<int *&&>);
	CHECK(nstd::is_reference_v<const int *&&>);

	class A {};
	CHECK(!nstd::is_reference_v<A>);
	CHECK(nstd::is_reference_v<A &>);
	CHECK(nstd::is_reference_v<const A &>);
	CHECK(nstd::is_reference_v<const A &&>);
}

TEST_CASE("is_pointer") {
	CHECK(!nstd::is_pointer_v<int>);
	CHECK(nstd::is_pointer_v<int *>);
	CHECK(nstd::is_pointer_v<int *const>);
	CHECK(nstd::is_pointer_v<const int *>);
	CHECK(nstd::is_pointer_v<const int *const>);
	CHECK(nstd::is_pointer_v<const volatile int *const>);
	CHECK(nstd::is_pointer_v<const volatile int *const volatile>);
	CHECK(nstd::is_pointer_v<float **>);
	CHECK(!nstd::is_pointer_v<int &>);
	CHECK(nstd::is_pointer_v<int (*)()>);
	CHECK(!nstd::is_pointer_v<int[42]>);    // NOTE: array is not pointer
	CHECK(!nstd::is_pointer_v<int[]>);      // NOTE: array is not pointer
	CHECK(!nstd::is_pointer_v<nullptr_t>);  // NOTE: nullptr is not pointer

	struct A {
		int a;
		void b();
		void c();
	};

	CHECK(!nstd::is_pointer_v<decltype(&A::a)>);
	CHECK(!nstd::is_pointer_v<decltype(&A::b)>);
}

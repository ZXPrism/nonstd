#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <util/nstd_type_traits.h>

#include <type_traits>

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

	CHECK(nstd::is_same_v<nstd::conditional<true, int, float>::type,
	                      std::conditional<true, int, float>::type>);
	CHECK(nstd::is_same_v<std::conditional_t<true, int, float>,
	                      std::conditional_t<true, int, float>>);
	CHECK(nstd::is_same_v<nstd::conditional_t<false, int, float>,
	                      std::conditional_t<false, int, float>>);
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

	CHECK(nstd::is_same_v<nstd::remove_const_t<const char *>, std::remove_const_t<const char *>>);
	CHECK(nstd::is_same_v<nstd::remove_const_t<char *const>, std::remove_const_t<char *const>>);
	CHECK(nstd::is_same_v<nstd::remove_const_t<const char &>, std::remove_const_t<const char &>>);
}

TEST_CASE("remove_volatile") {
	CHECK(!nstd::is_volatile_v<nstd::remove_volatile<volatile int>::type>);
	CHECK(nstd::is_same_v<nstd::remove_volatile_t<volatile double>, double>);

	CHECK(nstd::is_same_v<nstd::remove_volatile_t<volatile double>, std::remove_volatile_t<volatile double>>);
}

TEST_CASE("remove_cv") {
	CHECK(!nstd::is_volatile_v<nstd::remove_cv<volatile int>::type>);
	CHECK(nstd::is_same_v<nstd::remove_cv_t<const volatile double>, double>);
	CHECK(nstd::is_same_v<nstd::remove_cv_t<const float>, float>);
	CHECK(nstd::is_same_v<nstd::remove_cv_t<volatile unsigned>, unsigned>);

	CHECK(nstd::is_same_v<nstd::remove_cv_t<const volatile double>, std::remove_cv_t<const volatile double>>);
	CHECK(nstd::is_same_v<nstd::remove_cv_t<const float>, std::remove_cv_t<const float>>);
	CHECK(nstd::is_same_v<nstd::remove_cv_t<volatile unsigned>, std::remove_cv_t<volatile unsigned>>);
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

	CHECK(nstd::is_same_v<nstd::remove_reference_t<int>, std::remove_reference_t<int>>);
	CHECK(nstd::is_same_v<nstd::remove_reference_t<char &>, std::remove_reference_t<char &>>);
	CHECK(nstd::is_same_v<nstd::remove_reference_t<float &&>, std::remove_reference_t<float &&>>);
	CHECK(nstd::is_same_v<nstd::remove_reference_t<const double &&>, std::remove_reference_t<const double &&>>);
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
	CHECK(!nstd::is_pointer_v<int[42]>);          // NOTE: array is not pointer
	CHECK(!nstd::is_pointer_v<int[]>);            // NOTE: array is not pointer
	CHECK(!nstd::is_pointer_v<nstd::nullptr_t>);  // NOTE: nullptr is not pointer

	struct A {
		int a;
		void b();
		void c();
	};

	CHECK(!nstd::is_pointer_v<decltype(&A::a)>);
	CHECK(!nstd::is_pointer_v<decltype(&A::b)>);
}

TEST_CASE("type_identity") {
	CHECK(nstd::is_same_v<int, nstd::type_identity_t<int>>);
	CHECK(nstd::is_same_v<int *, nstd::type_identity_t<int *>>);
	CHECK(nstd::is_same_v<int &, nstd::type_identity_t<int &>>);
	CHECK(nstd::is_same_v<int *&, nstd::type_identity_t<int *&>>);

	CHECK(nstd::is_same_v<nstd::type_identity_t<int>, std::type_identity_t<int>>);
	CHECK(nstd::is_same_v<nstd::type_identity_t<int *>, std::type_identity_t<int *>>);
	CHECK(nstd::is_same_v<nstd::type_identity_t<int &>, std::type_identity_t<int &>>);
	CHECK(nstd::is_same_v<nstd::type_identity_t<int *&>, std::type_identity_t<int *&>>);
}

TEST_CASE("remove_pointer") {
	CHECK(!nstd::is_pointer_v<nstd::remove_pointer_t<int>>);
	CHECK(!nstd::is_pointer_v<nstd::remove_pointer_t<int *>>);
	CHECK(nstd::is_pointer_v<nstd::remove_pointer_t<int **>>);
	CHECK(!nstd::is_pointer_v<nstd::remove_pointer_t<const int *>>);
	CHECK(nstd::is_pointer_v<nstd::remove_pointer_t<const int **>>);
	CHECK(nstd::is_pointer_v<nstd::remove_pointer_t<const int **const volatile>>);
	CHECK(nstd::is_pointer_v<nstd::remove_pointer_t<int (**)(int hel, bool lo, char world)>>);
	CHECK(!nstd::is_pointer_v<nstd::remove_pointer_t<int *&>>);
	CHECK(nstd::is_pointer_v<nstd::remove_pointer_t<nstd::remove_reference_t<int **&>>>);

	CHECK(nstd::is_same_v<nstd::remove_pointer_t<int>, int>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<int *>, int>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<int **>, int *>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<const int *>, const int>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<const int **>, const int *>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<const int **const volatile>, const int *>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<int (**)(int hel, bool lo, char world)>, int (*)(int, bool, char)>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<int *&>, int *&>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<nstd::remove_reference_t<int **&>>, int *>);

	struct A {
		void foo();
		void bar();
	};

	CHECK(nstd::is_same_v<nstd::remove_pointer_t<decltype(&A::foo)>, decltype(&A::foo)>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<void (A::**)()>, decltype(&A::foo)>);

	CHECK(nstd::is_same_v<nstd::remove_pointer_t<int>,
	                      std::remove_pointer_t<int>>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<int *>,
	                      std::remove_pointer_t<int *>>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<int **>,
	                      std::remove_pointer_t<int **>>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<const int *>,
	                      std::remove_pointer_t<const int *>>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<const int **>,
	                      std::remove_pointer_t<const int **>>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<const int **const volatile>,
	                      std::remove_pointer_t<const int **const volatile>>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<int (**)(int hel, bool lo, char world)>,
	                      std::remove_pointer_t<int (**)(int hel, bool lo, char world)>>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<int *&>,
	                      std::remove_pointer_t<int *&>>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<nstd::remove_reference_t<int **&>>,
	                      std::remove_pointer_t<nstd::remove_reference_t<int **&>>>);

	CHECK(nstd::is_same_v<nstd::remove_pointer_t<decltype(&A::foo)>,
	                      std::remove_pointer_t<decltype(&A::foo)>>);
	CHECK(nstd::is_same_v<nstd::remove_pointer_t<void (A::**)()>,
	                      std::remove_pointer_t<void (A::**)()>>);
}

TEST_CASE("add_pointer") {
	CHECK(nstd::is_same_v<nstd::add_pointer_t<int>, int *>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<int *>, int **>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<int *const>, int *const *>);
	CHECK(!nstd::is_same_v<nstd::add_pointer_t<int *const>, int **const>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<void(int x)>, void (*)(int y)>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<int &>, int *>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<const int &>, const int *>);

	struct A {
		void foo();
		void bar();
	};

	CHECK(!nstd::is_same_v<nstd::add_pointer_t<decltype(&A::foo)>, decltype(&A::foo)>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<decltype(&A::bar)>, void (A::**)()>);

	CHECK(nstd::is_same_v<nstd::add_pointer_t<int>,
	                      std::add_pointer_t<int>>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<int *>,
	                      std::add_pointer_t<int *>>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<int *const>,
	                      std::add_pointer_t<int *const>>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<void(int x)>,
	                      std::add_pointer_t<void(int x)>>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<int &>,
	                      std::add_pointer_t<int &>>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<const int &>,
	                      std::add_pointer_t<const int &>>);

	CHECK(nstd::is_same_v<nstd::add_pointer_t<decltype(&A::foo)>,
	                      std::add_pointer_t<decltype(&A::foo)>>);
	CHECK(nstd::is_same_v<nstd::add_pointer_t<decltype(&A::bar)>,
	                      std::add_pointer_t<decltype(&A::bar)>>);
}

namespace test_conjunction {

template<typename Ty1, typename... Tyn>
constexpr bool all_types_same() {
	return nstd::conjunction_v<nstd::is_same<Ty1, Tyn>...>;
}

}  // namespace test_conjunction

TEST_CASE("conjunction") {
	CHECK(test_conjunction::all_types_same<int, int, int>());
	CHECK(!test_conjunction::all_types_same<int, int &, int>());
	CHECK(!test_conjunction::all_types_same<int, int, const int>());
	CHECK(test_conjunction::all_types_same<int(int hello), int(int hi), int(int howru)>());
	CHECK(!test_conjunction::all_types_same<int, float, int>());
}

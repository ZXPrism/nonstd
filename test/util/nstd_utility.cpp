#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <util/nstd_utility.h>

#include <utility>

namespace test_forward {

template<typename Ty>
constexpr bool proc(Ty &) {
	return true;
}

template<typename Ty>
constexpr bool proc(Ty &&) {
	return false;
}

template<typename Ty>
constexpr bool wrapper_bad(Ty &&x) {
	return proc<Ty>(x);  // bad: x is lvalue, so always call lvalue overload :(
}

template<typename Ty>
constexpr bool wrapper_good(Ty &&x) {
	return proc<Ty>(nstd::forward<Ty>(x));  // good: can decide overload based on Ty&&'s deduced type :)
}

}  // namespace test_forward

TEST_CASE("forward") {
	class A {
	public:
		consteval int foo() & {
			return 0;
		}

		consteval int foo() && {
			return 1;
		}
	};

	A a;
	CHECK_EQ(a.foo(), 0);
	CHECK_EQ(A().foo(), 1);
	CHECK_EQ(nstd::forward<A &>(a).foo(), 0);
	CHECK_EQ(nstd::forward<A>(A()).foo(), 1);

	CHECK_EQ(nstd::forward<A &>(a).foo(), std::forward<A &>(a).foo());
	CHECK_EQ(nstd::forward<A>(A()).foo(), std::forward<A>(A()).foo());

	CHECK(!test_forward::wrapper_good(42));
	CHECK(test_forward::wrapper_good(a));
	CHECK(test_forward::wrapper_bad(42));
	CHECK(test_forward::wrapper_bad(a));
}

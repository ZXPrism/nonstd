#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <util/nstd_utility.h>

#include <utility>

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

	CHECK_EQ(nstd::forward<A>(A()).foo(), std::forward<A>(A()).foo());
	CHECK_EQ(nstd::forward<A>(A()).foo(), std::forward<A>(A()).foo());
}

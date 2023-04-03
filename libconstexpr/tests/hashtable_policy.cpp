#include <libconstexpr/hashtable_policy.h>

#include <cstddef>
#include <catch2/catch_test_macros.hpp>

constexpr bool is_prime(std::size_t n) {
    if (n <= 1) {
        return false;
    }

    for (std::size_t divisor = 2; divisor < n; ++divisor) {
        if (n % divisor == 0) {
            return false;
        }
    }

    return true;
}

SCENARIO("size policies provide sizes", "[libconstexpr]") {
    GIVEN("a prime size policy") {
        using policy = libconstexpr::hashtable::prime_size_policy;

        STATIC_REQUIRE(libconstexpr::hashtable::size_policy_concept<policy>);

        WHEN("a next size is requested") {
            constexpr std::size_t n{1000uz};
            constexpr auto size = policy::next(n);

            THEN("the size is higher or equal to the number of elements") {
                STATIC_REQUIRE(size >= n);
            }

            THEN("the size is prime") { STATIC_REQUIRE(is_prime(size)); }
        }
    }
}

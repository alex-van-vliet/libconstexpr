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

SCENARIO("nodes contain a value", "[libconstexpr]") {
    using namespace libconstexpr;
    GIVEN("a hash-less node with an int") {
        constexpr hashtable::hashless_node<hash<int>, int> node{2};

        STATIC_REQUIRE(hashtable::node_concept<decltype(node), int>);

        WHEN("its value is requested") {
            THEN("its value is the given one") {
                STATIC_REQUIRE(node.value == 2);
            }
        }

        WHEN("its hash is requested") {
            THEN("its hash is provided") { STATIC_REQUIRE(node.hash() == 2uz); }
        }
    }
    GIVEN("a hash-full node with an int") {
        constexpr hashtable::hashfull_node<hash<int>, int> node{3};

        STATIC_REQUIRE(hashtable::node_concept<decltype(node), int>);

        WHEN("its value is requested") {
            THEN("its value is the given one") {
                STATIC_REQUIRE(node.value == 3);
            }
        }

        WHEN("its hash is requested") {
            THEN("its hash is provided") { STATIC_REQUIRE(node.hash() == 3uz); }
        }
    }
    GIVEN("a hash-full node with an int and a given hash") {
        constexpr hashtable::hashfull_node<hash<int>, int> node{3, 0uz};

        STATIC_REQUIRE(hashtable::node_concept<decltype(node), int>);

        WHEN("its value is requested") {
            THEN("its value is the given one") {
                STATIC_REQUIRE(node.value == 3);
            }
        }

        WHEN("its hash is requested") {
            THEN("its hash is provided") { STATIC_REQUIRE(node.hash() == 0uz); }
        }
    }
}

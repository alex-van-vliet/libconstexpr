#include <libconstexpr/hash.h>

#include <cstddef>
#include <catch2/catch_test_macros.hpp>
#include <type_traits>

SCENARIO("values can be hashed", "[libconstexpr]") {
    GIVEN("Two integers") {
        const int i{3};
        const int j{4};

        WHEN("their hash is computed") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::hash<int>{}(i)),
                               std::size_t>);

            constexpr auto hash_i = libconstexpr::hash<int>{}(i);
            constexpr auto hash_j = libconstexpr::hash<int>{}(j);

            THEN("their hash is different") {
                STATIC_REQUIRE(hash_i != hash_j);
            }
        }
    }
    GIVEN("Two std::size_t") {
        const std::size_t i{6};
        const std::size_t j{10};

        WHEN("their hash is computed") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::hash<std::size_t>{}(i)),
                               std::size_t>);

            constexpr auto hash_i = libconstexpr::hash<std::size_t>{}(i);
            constexpr auto hash_j = libconstexpr::hash<std::size_t>{}(j);

            THEN("their hash is different") {
                STATIC_REQUIRE(hash_i != hash_j);
            }
        }
    }
}

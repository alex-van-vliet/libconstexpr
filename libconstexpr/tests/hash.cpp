#include <libconstexpr/hash.h>

#include <cstddef>
#include <string>
#include <catch2/catch_test_macros.hpp>
#include <type_traits>

SCENARIO("values can be hashed", "[libconstexpr]") {
    GIVEN("Two integers") {
        constexpr int i{3};
        constexpr int j{4};

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
        constexpr std::size_t i{6};
        constexpr std::size_t j{10};

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

    GIVEN("A null pointer") {
        constexpr std::nullptr_t i{nullptr};

        WHEN("its hash is computed") {
            STATIC_REQUIRE(std::is_same_v<
                           decltype(libconstexpr::hash<std::nullptr_t>{}(i)),
                           std::size_t>);

            constexpr auto hash_i = libconstexpr::hash<std::nullptr_t>{}(i);

            THEN("its hash is 0") { STATIC_REQUIRE(hash_i == 0); }
        }
    }

    GIVEN("Two strings") {
        constexpr char i[6]{"hello"};
        constexpr char j[5]{"test"};

        WHEN("their hash is computed") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::hash<std::string>{}(
                                   std::string(i, i + sizeof(i) - 1))),
                               std::size_t>);

            constexpr auto hash_i = libconstexpr::hash<std::string>{}(
                std::string(i, i + sizeof(i) - 1));
            constexpr auto hash_j = libconstexpr::hash<std::string>{}(
                std::string(j, j + sizeof(j) - 1));

            THEN("their hash is different") {
                STATIC_REQUIRE(hash_i != hash_j);
            }
        }
    }
}

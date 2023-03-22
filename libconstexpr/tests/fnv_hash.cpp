#include <libconstexpr/fnv_hash.h>

#include <cstddef>
#include <catch2/catch_test_macros.hpp>

SCENARIO("fnv hash hashes bytes using the fnv algorithm", "[libconstexpr]") {
    GIVEN("A char array") {
        constexpr char s[6]{"hello"};

        WHEN("its hash is computed in 32 bits") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::fnv1a_hash_bytes<
                                        std::uint32_t>(s, s + sizeof(s) - 1)),
                               std::uint32_t>);

            constexpr auto hash = libconstexpr::fnv1a_hash_bytes<std::uint32_t>(
                s, s + sizeof(s) - 1);
            constexpr auto expected = 0x4f9f2cab;

            THEN("its value is correct") { STATIC_REQUIRE(hash == expected); }
        }

        WHEN("its hash is computed in 64 bits") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::fnv1a_hash_bytes<
                                        std::uint64_t>(s, s + sizeof(s) - 1)),
                               std::uint64_t>);

            constexpr auto hash = libconstexpr::fnv1a_hash_bytes<std::uint64_t>(
                s, s + sizeof(s) - 1);
            constexpr auto expected = 0xa430d84680aabd0b;

            THEN("its value is correct") { STATIC_REQUIRE(hash == expected); }
        }
    }
}

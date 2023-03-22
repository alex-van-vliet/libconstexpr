#include <libconstexpr/fnv_hash.h>

#include <cstddef>
#include <catch2/catch_test_macros.hpp>

SCENARIO("fnv hash hashes bytes using the fnv algorithm", "[libconstexpr]") {
    GIVEN("A char array") {
        constexpr char s[13]{"Hello, you !"};

        WHEN("its hash is computed in 32 bits") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::fnv1a_hash_bytes<
                                        std::uint32_t>(s, sizeof(s) - 1)),
                               std::uint32_t>);

            constexpr auto hash =
                libconstexpr::fnv1a_hash_bytes<std::uint32_t>(s, sizeof(s) - 1);
            constexpr std::uint32_t expected{0x97d6c079};

            THEN("its value is correct") { STATIC_REQUIRE(hash == expected); }
        }

        WHEN("its hash is computed in 64 bits") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::fnv1a_hash_bytes<
                                        std::uint64_t>(s, sizeof(s) - 1)),
                               std::uint64_t>);

            constexpr auto hash =
                libconstexpr::fnv1a_hash_bytes<std::uint64_t>(s, sizeof(s) - 1);
            constexpr std::uint64_t expected{0x47369472d439c3d9};

            THEN("its value is correct") { STATIC_REQUIRE(hash == expected); }
        }

        WHEN("its has is computed in 64 bits converting it to a int32 array") {
            static_assert(sizeof(s) % 4 == 1);

            auto ptr = reinterpret_cast<const std::uint32_t*>(s);

            auto hash = libconstexpr::fnv1a_hash_bytes<std::uint64_t>(
                ptr, sizeof(s) / 4);
            constexpr std::uint64_t expected{0x47369472d439c3d9};

            THEN("its value is the same as computed using a char array") {
                REQUIRE(hash == expected);
            }
        }
    }
}

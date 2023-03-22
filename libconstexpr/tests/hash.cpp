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

    GIVEN("Two wchar strings") {
        constexpr wchar_t i[6]{L"hello"};
        constexpr wchar_t j[5]{L"test"};

        WHEN("their hash is computed") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::hash<std::wstring>{}(
                                   std::wstring(i, i + sizeof(i) - 1))),
                               std::size_t>);

            constexpr auto hash_i = libconstexpr::hash<std::wstring>{}(
                std::wstring(i, i + sizeof(i) / sizeof(wchar_t) - 1));
            constexpr auto hash_j = libconstexpr::hash<std::wstring>{}(
                std::wstring(j, j + sizeof(j) / sizeof(wchar_t) - 1));

            THEN("their hash is different") {
                STATIC_REQUIRE(hash_i != hash_j);
            }
        }
    }

    GIVEN("Two char8 strings") {
        constexpr char8_t i[6]{u8"hello"};
        constexpr char8_t j[5]{u8"test"};

        WHEN("their hash is computed") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::hash<std::u8string>{}(
                                   std::u8string(i, i + sizeof(i) - 1))),
                               std::size_t>);

            constexpr auto hash_i = libconstexpr::hash<std::u8string>{}(
                std::u8string(i, i + sizeof(i) / sizeof(char8_t) - 1));
            constexpr auto hash_j = libconstexpr::hash<std::u8string>{}(
                std::u8string(j, j + sizeof(j) / sizeof(char8_t) - 1));

            THEN("their hash is different") {
                STATIC_REQUIRE(hash_i != hash_j);
            }
        }
    }

    GIVEN("Two char16 strings") {
        constexpr char16_t i[6]{u"hello"};
        constexpr char16_t j[5]{u"test"};

        WHEN("their hash is computed") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::hash<std::u16string>{}(
                                   std::u16string(i, i + sizeof(i) - 1))),
                               std::size_t>);

            constexpr auto hash_i = libconstexpr::hash<std::u16string>{}(
                std::u16string(i, i + sizeof(i) / sizeof(char16_t) - 1));
            constexpr auto hash_j = libconstexpr::hash<std::u16string>{}(
                std::u16string(j, j + sizeof(j) / sizeof(char16_t) - 1));

            THEN("their hash is different") {
                STATIC_REQUIRE(hash_i != hash_j);
            }
        }
    }

    GIVEN("Two char32 strings") {
        constexpr char32_t i[6]{U"hello"};
        constexpr char32_t j[5]{U"test"};

        WHEN("their hash is computed") {
            STATIC_REQUIRE(
                std::is_same_v<decltype(libconstexpr::hash<std::u32string>{}(
                                   std::u32string(i, i + sizeof(i) - 1))),
                               std::size_t>);

            constexpr auto hash_i = libconstexpr::hash<std::u32string>{}(
                std::u32string(i, i + sizeof(i) / sizeof(char32_t) - 1));
            constexpr auto hash_j = libconstexpr::hash<std::u32string>{}(
                std::u32string(j, j + sizeof(j) / sizeof(char32_t) - 1));

            THEN("their hash is different") {
                STATIC_REQUIRE(hash_i != hash_j);
            }
        }
    }
}

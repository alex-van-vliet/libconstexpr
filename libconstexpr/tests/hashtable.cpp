#include <libconstexpr/hashtable.h>

#include <cstddef>
#include <catch2/catch_test_macros.hpp>
#include <libconstexpr/hash.h>

SCENARIO("hash table is a set or a map", "[libconstexpr]") {
    GIVEN("a hash table with the value type being the key type (a set)") {
        using element_type = int;

        using node = libconstexpr::detail::hashless_node<
            libconstexpr::hash<element_type>, std::equal_to<element_type>,
            element_type>;

        using hashtable =
            libconstexpr::hashtable<element_type, element_type,
                                    std::allocator<element_type>, node,
                                    libconstexpr::detail::prime_size_policy>;

        hashtable set;
    }

    GIVEN("a hash table with the value type being a pair (a map)") {
        using key_type = int;
        using type = char;
        using value_type = std::pair<const key_type, type>;

        using node = libconstexpr::detail::hashless_node<
            decltype([](const value_type& value) {
                return libconstexpr::hash<key_type>{}(std::get<0>(value));
            }),
            std::equal_to<value_type>, value_type>;

        using hashtable =
            libconstexpr::hashtable<key_type, value_type, std::allocator<type>,
                                    node,
                                    libconstexpr::detail::prime_size_policy>;
    }
}

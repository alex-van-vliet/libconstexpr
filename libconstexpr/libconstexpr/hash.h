#ifndef LIBCONSTEXPR_HASH_H
#define LIBCONSTEXPR_HASH_H

#include <string>
#include <type_traits>
#include "fnv_hash.h"

namespace libconstexpr {
    template <typename T>
    struct hash;

    template <typename T>
    requires(std::is_integral_v<T>)
    struct hash<T> {
        constexpr std::size_t operator()(T t) { return t; }
    };

    template <>
    struct hash<std::nullptr_t> {
        constexpr std::size_t operator()(std::nullptr_t) { return 0; }
    };

    template <typename T>
    struct hash<T*> {
        // Reinterpreting a pointer to a std::size_t at compile-time is
        // forbidden both with reinterpret_cast and bit_cast. To prevent
        // confusion when using constexpr containers, no implementation
        // for hashing a pointer is provided.
    };

    template <typename CharType>
    struct hash<std::basic_string<CharType>> {
        constexpr std::size_t operator()(const std::basic_string<CharType>& s) {
            return fnv1a_hash_bytes(s.data(), s.length());
        }
    };
} // namespace libconstexpr

#endif // LIBCONSTEXPR_HASH_H

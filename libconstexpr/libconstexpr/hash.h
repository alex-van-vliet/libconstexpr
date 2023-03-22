#ifndef LIBCONSTEXPR_HASH_H
#define LIBCONSTEXPR_HASH_H

#include <type_traits>

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
} // namespace libconstexpr

#endif // LIBCONSTEXPR_HASH_H

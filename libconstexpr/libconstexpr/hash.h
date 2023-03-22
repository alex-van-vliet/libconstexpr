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
} // namespace libconstexpr

#endif // LIBCONSTEXPR_HASH_H

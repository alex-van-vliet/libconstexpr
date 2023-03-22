#ifndef LIBCONSTEXPR_FNV_HASH_H
#define LIBCONSTEXPR_FNV_HASH_H

#include <bit>
#include <cstddef>
#include <type_traits>

namespace libconstexpr {
    template <typename ResultType = std::size_t>
    struct fnv_parameters;

    template <typename ResultType>
    requires(sizeof(ResultType) == 4)
    struct fnv_parameters<ResultType> {
        constexpr static ResultType offset_prime{0x01000193};
        constexpr static ResultType offset_basis{0x811c9dc5};
    };

    template <typename ResultType>
    requires(sizeof(ResultType) == 8)
    struct fnv_parameters<ResultType> {
        constexpr static ResultType offset_prime{0x00000100000001B3};
        constexpr static ResultType offset_basis{0xcbf29ce484222325};
    };

    template <typename ElementType>
    constexpr unsigned char get_byte(ElementType element, std::size_t byte) {
        static_assert((std::endian::native == std::endian::big) ||
                      (std::endian::native == std::endian::little) ||
                      (sizeof(ElementType) == 1));
        if constexpr (sizeof(ElementType) == 1) {
            return element;
        } else if constexpr (std::endian::native == std::endian::little) {
            return static_cast<std::size_t>(element) >> (8 * byte);
        } else {
            return static_cast<std::size_t>(element) >>
                   (8 * (sizeof(ElementType) - byte - 1));
        }
    }

    template <typename ResultType = std::size_t, typename ElementType>
    requires(std::is_integral_v<ElementType>)
    constexpr ResultType fnv1a_hash_bytes(const ElementType* element,
                                          std::size_t n_elements) {
        ResultType hash{fnv_parameters<ResultType>::offset_basis};

        for (; n_elements > 0; --n_elements, ++element) {
            for (std::size_t i = 0; i < sizeof(ElementType); ++i) {
                hash = hash ^ get_byte(*element, i);

                hash = hash * fnv_parameters<ResultType>::offset_prime;
            }
        }

        return hash;
    }
} // namespace libconstexpr

#endif // LIBCONSTEXPR_FNV_HASH_H

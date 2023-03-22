#ifndef LIBCONSTEXPR_FNV_HASH_H
#define LIBCONSTEXPR_FNV_HASH_H

#include <cstddef>

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

    template <typename ResultType = std::size_t, typename It>
    constexpr ResultType fnv1a_hash_bytes(It begin, It end) {
        ResultType hash{fnv_parameters<ResultType>::offset_basis};

        for (; begin != end; ++begin) {
            hash = hash ^ static_cast<unsigned char>(*begin);
            hash = hash * fnv_parameters<ResultType>::offset_prime;
        }

        return hash;
    }
} // namespace libconstexpr

#endif // LIBCONSTEXPR_FNV_HASH_H

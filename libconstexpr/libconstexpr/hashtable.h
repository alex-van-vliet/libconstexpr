#ifndef LIBCONSTEXPR_HASHTABLE_H
#define LIBCONSTEXPR_HASHTABLE_H

#include "hashtable_policy.h"

namespace libconstexpr {
    template <typename Key, typename Value, typename Allocator, typename Node,
              typename Policy>
    requires detail::node_concept<Node, Value> &&
             detail::size_policy_concept<Policy>
    struct hashtable {};
} // namespace libconstexpr

#endif // LIBCONSTEXPR_HASHTABLE_H

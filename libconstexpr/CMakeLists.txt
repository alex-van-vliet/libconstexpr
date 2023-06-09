add_library(libconstexpr INTERFACE
        libconstexpr/fnv_hash.h
        libconstexpr/hash.h
        libconstexpr/hashtable.h
        libconstexpr/hashtable_policy.h
        )
target_include_directories(libconstexpr INTERFACE .)

add_executable(tests_hash tests/hash.cpp)
target_link_libraries(tests_hash PRIVATE libconstexpr)
target_link_libraries(tests_hash PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(tests_hash)

add_executable(tests_hashtable tests/hashtable.cpp)
target_link_libraries(tests_hashtable PRIVATE libconstexpr)
target_link_libraries(tests_hashtable PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(tests_hashtable)

add_executable(tests_hashtable_policy tests/hashtable_policy.cpp)
target_link_libraries(tests_hashtable_policy PRIVATE libconstexpr)
target_link_libraries(tests_hashtable_policy PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(tests_hashtable_policy)

add_executable(tests_fnv_hash tests/fnv_hash.cpp)
target_link_libraries(tests_fnv_hash PRIVATE libconstexpr)
target_link_libraries(tests_fnv_hash PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(tests_fnv_hash)

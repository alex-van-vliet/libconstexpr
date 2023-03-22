add_library(libconstexpr INTERFACE libconstexpr/hash.h)
target_include_directories(libconstexpr INTERFACE .)

add_executable(tests_hash tests/hash.cpp)
target_link_libraries(tests_hash PRIVATE libconstexpr)
target_link_libraries(tests_hash PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(tests_hash)

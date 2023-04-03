cmake_minimum_required(VERSION 3.24)
project(libconstexpr)

set(CMAKE_CXX_STANDARD 23)

include(CTest)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.3.2
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(Catch)

find_package(Catch2 3 REQUIRED)

add_subdirectory(libconstexpr)

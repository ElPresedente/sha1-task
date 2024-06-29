cmake_minimum_required(VERSION 3.5)
set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")
project(sha1_task)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem range)
find_package(argparse CONFIG REQUIRED)

add_executable(sha1_task main.cpp
        Application.cpp
        Result.cpp
        Result.hpp
)
target_link_libraries(sha1_task
        argparse::argparse
        Boost::filesystem
        Boost::range
        OpenSSL::Crypto
)
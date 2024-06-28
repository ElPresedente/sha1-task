cmake_minimum_required(VERSION 3.5)
set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")
project(sha1_task)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(argparse CONFIG REQUIRED)

add_executable(sha1_task main.cpp)
target_link_libraries(sha1_task
        argparse::argparse
        Boost::filesystem
        OpenSSL::Crypto
)
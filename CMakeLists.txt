project(btc++)

cmake_minimum_required (VERSION 3.0.2)

################################################################################

set(CMAKE_CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -lcrypto -fopenmp")

find_package(OpenSSL REQUIRED)
find_package(Boost 1.72.0 REQUIRED)

################################################################################

include_directories("${CMAKE_SOURCE_DIR}/include/")
file(GLOB sources "${CMAKE_SOURCE_DIR}/src/*.cpp")

################################################################################

add_executable(btc++ ${sources})

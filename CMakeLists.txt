project(BTC++)

cmake_minimum_required (VERSION 3.0.2)

option(USE_CUDA "Use CUDA" ON)

################################################################################

set(CMAKE_CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -lcrypto -fopenmp -lboost_filesystem -lboost_system")


find_package(OpenSSL REQUIRED)
find_package(Boost 1.58.0 REQUIRED)
find_package(CUDA REQUIRED)

################################################################################

if(USE_CUDA)
    add_subdirectory(${CMAKE_SOURCE_DIR}/cuda)

    add_definitions(-DUSE_CUDA)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

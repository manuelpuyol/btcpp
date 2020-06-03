project(btc++ LANGUAGES CXX)

cmake_minimum_required (VERSION 3.0.2)

option(USE_CUDA "Use CUDA" ON)

################################################################################

set(CMAKE_CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -lcrypto -fopenmp")


find_package(OpenSSL REQUIRED)
find_package(Boost 1.72.0 REQUIRED)
find_package(CUDA REQUIRED)

################################################################################

file(GLOB sources "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB cuda "${CMAKE_SOURCE_DIR}/src/*.cu")

################################################################################

if(USE_CUDA)
    include_directories("/opt/cuda/include/")

    set(CMAKE_CUDA_STANDARD 14)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
    enable_language("CUDA")

    add_library(gpu SHARED ${cuda})
    target_include_directories(gpu PUBLIC "${CMAKE_SOURCE_DIR}/cuda_include/")
    set_target_properties(gpu PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

    add_executable(btc++ ${sources})
    target_include_directories(btc++ PUBLIC "${CMAKE_SOURCE_DIR}/include/")

    target_link_libraries(btc++ gpu)

    add_definitions(-DUSE_CUDA)
else(USE_CUDA)
    add_executable(btc++ ${sources})
endif()

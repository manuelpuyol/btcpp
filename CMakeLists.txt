project(btc++ LANGUAGES CXX)

cmake_minimum_required (VERSION 3.0.2)

option(USE_CUDA "Use CUDA" ON)

################################################################################

set(CMAKE_CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -lcrypto -fopenmp")

if(USE_CUDA)
    set(CMAKE_CUDA_STANDARD 14)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()

find_package(OpenSSL REQUIRED)
find_package(Boost 1.72.0 REQUIRED)

################################################################################

include_directories("${CMAKE_SOURCE_DIR}/include/")
file(GLOB sources "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB cuda "${CMAKE_SOURCE_DIR}/src/*.cu")

################################################################################

if(USE_CUDA)
    enable_language("CUDA")
    add_library(gpu STATIC ${cuda})
    set_target_properties(gpu PROPERTIES CUDA_SEPARABLE_COMPILATION ON CUDA_STANDARD 14)

    add_executable(btc++ ${sources})
    set_property(TARGET btc++ PROPERTY CUDA_SEPARABLE_COMPILATION ON CUDA_STANDARD 14)
    target_link_libraries(btc++ PRIVATE gpu)
else(USE_CUDA)
    add_executable(btc++ ${cpu_source_files})
endif()

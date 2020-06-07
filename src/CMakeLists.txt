project(btc++ LANGUAGES CXX)

################################################################################

file(GLOB sources "${CMAKE_SOURCE_DIR}/src/*.cpp")
include_directories("${CMAKE_SOURCE_DIR}/include/")

################################################################################

add_executable(btc++ ${sources})

if(USE_CUDA)
    enable_language(CUDA)
    include_directories("${CMAKE_SOURCE_DIR}/cuda/include/" "/usr/local/cuda/include/")
    target_link_libraries(btc++ gpu)
endif()

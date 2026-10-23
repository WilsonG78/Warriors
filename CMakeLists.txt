cmake_minimum_required(VERSION 3.20)

project(Warriors VERSION 0.1.0 LANGUAGES CXX)

add_executable(warriors src/main.cpp)
target_compile_features(warriors PRIVATE cxx_std_20)
set_target_properties(warriors PROPERTIES CXX_EXTENSIONS OFF)

if(MSVC)
    target_compile_options(warriors PRIVATE /W4 /permissive- /utf-8)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(warriors PRIVATE -Wall -Wextra -Wpedantic)
endif()

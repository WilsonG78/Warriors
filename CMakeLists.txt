cmake_minimum_required(VERSION 3.28)

project(Warriors VERSION 0.1.0 LANGUAGES CXX)

add_executable(warriors
    src/main.cpp
    src/agents/basic_agent.cpp
    src/command/basic_commander.cpp
)
target_compile_features(warriors PRIVATE cxx_std_20)
set_target_properties(warriors PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(warriors PRIVATE src)

include(FetchContent)
FetchContent_Declare(
  EnTT
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG        v4.0.0
  GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(EnTT)
target_link_libraries(warriors PRIVATE EnTT::EnTT)

if(MSVC)
    target_compile_options(warriors PRIVATE /W4 /permissive- /utf-8)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(warriors PRIVATE -Wall -Wextra -Wpedantic)
endif()

cmake_minimum_required(VERSION 3.16)

project(RISC-V)

set(CMAKE_CXX_STANDARD 17)

# open o3
set(CMAKE_CXX_FlAGS "-O3")

# include directories
include_directories(src/include)

# add subdirectory
add_subdirectory(src)
add_subdirectory(test)

# add executable
add_executable(code main.cpp)
target_link_libraries(code source_shared)

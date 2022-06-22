cmake_minimum_required(VERSION 3.16)

project(RISC-V)

set(CMAKE_CXX_STANDARD 17)

# install googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# include directories
include_directories(src/include)

# add subdirectory
add_subdirectory(src)
add_subdirectory(test)


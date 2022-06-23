file(GLOB test_cpps */*.cpp)


# install googletest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# enable google test
include(GoogleTest)
enable_testing()

# connect them to google test
foreach(test_cpp IN LISTS test_cpps)
  get_filename_component(test_cpp_name ${test_cpp} NAME_WE)
  add_executable(${test_cpp_name} ${test_cpp})
  target_link_libraries(${test_cpp_name} source_shared gtest_main)
  gtest_discover_tests(${test_cpp_name})
endforeach()
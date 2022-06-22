file(GLOB test_cpps */*.cpp)

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
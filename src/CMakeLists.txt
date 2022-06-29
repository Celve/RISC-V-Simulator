file(GLOB source_cpps */*.cpp)

set(CMAKE_CXX_FLAGS "-O3")

add_library(source_shared STATIC ${source_cpps})

foreach(source_cpp IN LISTS source_cpps)
  message("Add ${source_cpp}")
endforeach()
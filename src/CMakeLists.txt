file(GLOB source_cpps */*.cpp)
add_library(source_shared STATIC ${source_cpps})

foreach(source_cpp IN LISTS source_cpps)
  message("Add ${source_cpp}")
endforeach()
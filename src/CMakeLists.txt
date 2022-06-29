file(GLOB source_cpps */*.cpp)

set(CMAKE_CXX_FlAGS "-O3")

add_library(source_shared STATIC ${source_cpps})

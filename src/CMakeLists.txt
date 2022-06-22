file(GLOB source_cpps */*.cpp)
add_library(source_shared SHARED ${source_cpps})
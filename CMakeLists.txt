cmake_minimum_required(VERSION 3.10)

project(Gadgets)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "$ CMake Targets")

add_subdirectory(lib)
add_subdirectory(src)

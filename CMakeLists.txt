cmake_minimum_required(VERSION 3.20)

project(Gadgets)

# set the standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# enable project folders for IDE projects (like Visual Studio)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "$ CMake Targets")

# include Gadget project rules
include(Tools/gadgets.cmake)

# include projects from lib/ and src/ folders
add_subdirectory(lib)
add_subdirectory(src)

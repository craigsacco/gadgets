# Copyright (c) 2024 Craig Sacco
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# SPDX-License-Identifier: MIT

# include google test and boost folders
add_subdirectory(googletest)
add_subdirectory(boost)

# when using GCC under Windows, CMake does not create the required folders prior to
# calling windmc.exe on boost/libs/log/src/windows/simple_event_log.mc - this is a
# workaround for that issue
if ((CMAKE_SYSTEM_NAME STREQUAL "Windows") AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    message("-- Gadgets: adding workaround for windmc.exe issue for boost_log")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/boost/libs/log/src/windows")
endif()

# set IDE folder to all targets in the current directory to "Libraries"
function(update_lib_properties __dir__)
    get_property(__targets__ DIRECTORY "${__dir__}" PROPERTY BUILDSYSTEM_TARGETS)
    foreach(__target__ IN LISTS __targets__)
        set_target_properties(${__target__} PROPERTIES FOLDER "Libraries")
    endforeach()
    get_property(__subdirs__ DIRECTORY "${__dir__}" PROPERTY SUBDIRECTORIES)
    foreach(__subdir__ IN LISTS __subdirs__)
        update_lib_properties("${__subdir__}")
    endforeach()
endfunction()
update_lib_properties(${CMAKE_CURRENT_SOURCE_DIR})

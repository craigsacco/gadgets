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

# common properties and definitions for all Gadgets projects
function(set_gadgets_target_options __target__ __alias__ __idefolder___)
    set_target_properties(${__target__} PROPERTIES
        FOLDER ${__idefolder___}
    )
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${__target__}
            PRIVATE /W4         # enable all level 4 warnings
                    /WX         # warnings as errors
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${__target__}
            PRIVATE -Wno-unknown-pragmas    # disable warnings regarding unknown pragmas (fixed in GCC 13.x)
                    -Wall                   # enable all other warnings
                    --pedantic
                    -Werror                 # warnings as errors
        )
    else()
        message(FATAL_ERROR "Compiler not supported")
    endif()
endfunction()

# definition for a Gadgets library
function(add_gadgets_library)
    cmake_parse_arguments(__arg "" "TARGET;ALIAS;IDEFOLDER" "" ${ARGN})
    add_library(${__arg_TARGET})
    add_library(${__arg_ALIAS} ALIAS ${__arg_TARGET})
    set_gadgets_target_options(${__arg_TARGET} ${__arg_ALIAS} ${__arg_IDEFOLDER})
endfunction()

# definition for a Gadgets hader-only library
function(add_gadgets_header_only_library)
    cmake_parse_arguments(__arg "" "TARGET;ALIAS;IDEFOLDER" "" ${ARGN})
    add_library(${__arg_TARGET} INTERFACE)
    add_library(${__arg_ALIAS} ALIAS ${__arg_TARGET})
    set_target_properties(${__arg_TARGET} PROPERTIES
        FOLDER ${__arg_IDEFOLDER}
    )
endfunction()

# definition for a Gadgets executable
function(add_gadgets_executable)
    cmake_parse_arguments(__arg "" "TARGET;ALIAS;IDEFOLDER" "" ${ARGN})
    add_executable(${__arg_TARGET})
    add_executable(${__arg_ALIAS} ALIAS ${__arg_TARGET})
    set_gadgets_target_options(${__arg_TARGET} ${__arg_ALIAS} ${__arg_IDEFOLDER})

    # add libws2_32.a as a link dependency for Windows executables
    # built using GCC (Boost::asio requires this)
    if((CMAKE_SYSTEM_NAME STREQUAL "Windows") AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
        target_link_libraries(${__arg_TARGET} PUBLIC wsock32 ws2_32)
    endif()
endfunction()

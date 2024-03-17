# common properties and definitions for all Gadgets projects
function(set_gadgets_target_options __target__ __alias__ __idefolder___)
    set_target_properties(${__target__} PROPERTIES
        FOLDER ${__idefolder___}
    )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${__target__}
            PRIVATE /W4         # enable all level 4 warnings
                    /WX         # warnings as errors
        )
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${__target__}
            PRIVATE -Wall       # enable all level 4 warnings
                    -Werror     # warnings as errors
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

# definition for a Gadgets executable
function(add_gadgets_executable)
    cmake_parse_arguments(__arg "" "TARGET;ALIAS;IDEFOLDER" "" ${ARGN})
    add_executable(${__arg_TARGET})
    add_executable(${__arg_ALIAS} ALIAS ${__arg_TARGET})
    set_gadgets_target_options(${__arg_TARGET} ${__arg_ALIAS} ${__arg_IDEFOLDER})

    # add winsock2 as a link dependency for Windows executables
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows") 
        target_link_libraries(${__arg_TARGET} PRIVATE wsock32 ws2_32)
    endif()
endfunction()

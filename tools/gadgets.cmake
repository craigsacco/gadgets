# common properties and definitions for all Gadgets projects
function(set_gadgets_target_options __target__ __alias__ __idefolder___)
    set_target_properties(${__target__} PROPERTIES
        FOLDER ${__idefolder___}
    )
    if(MSVC)
        target_compile_options(${__target__}
            PRIVATE /W4         # show all compiler warnings
                    /WX         # warnings as errors
        )
        add_compile_options(/Wall /WX)
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
endfunction()


cmake_minimum_required(VERSION 3.20)

project(Gadgets)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(set_gadgets_target_options __name__ __alias__ __idefolder___)
    set_target_properties(${__name__} PROPERTIES
        FOLDER ${__idefolder___}
    )
    if(MSVC)
        target_compile_options(${__name__}
            PRIVATE /W4         # show all compiler warnings
                    /WX         # warnings as errors
        )
        add_compile_options(/Wall /WX)
    endif()
endfunction()

function(add_gadgets_library __name__ __alias__ __idefolder___)
    add_library(${__name__})
    add_library(${__alias__} ALIAS ${__name__})
    set_gadgets_target_options(${__name__} ${__alias__} ${__idefolder___})
endfunction()

function(add_gadgets_executable __name__ __alias__ __idefolder___)
    add_executable(${__name__})
    add_executable(${__alias__} ALIAS ${__name__})
    set_gadgets_target_options(${__name__} ${__alias__} ${__idefolder___})
endfunction()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "$ CMake Targets")

add_compile_definitions(_WIN32_WINNT=0x0601)

add_subdirectory(lib)
add_subdirectory(src)

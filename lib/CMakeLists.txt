# boost needs this to silence some compiler warnings
add_compile_definitions(_WIN32_WINNT=0x0601)

# include google test and boost folders
add_subdirectory(googletest)
add_subdirectory(boost)

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

# include google test and boost folders
add_subdirectory(googletest)
add_subdirectory(boost)

# when using GCC under Windows, CMake does not create the required folders prior to
# calling windmc.exe on boost/libs/log/src/windows/simple_event_log.mc - this is a
# workaround for that issue
if ((CMAKE_SYSTEM_NAME STREQUAL "Windows") AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    message("Adding workaround for windmc.exe issue for boost_log")
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

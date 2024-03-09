add_executable(GadgetsTestRunner)

target_include_directories(GadgetsTestRunner
    PRIVATE include
            src
)

target_link_libraries(GadgetsTestRunner
    PUBLIC  Gadgets::Core
            gmock
            gtest
)

target_sources(GadgetsTestRunner
    PRIVATE src/main.cpp
            src/SemaphoreTests.cpp
)

set_target_properties(GadgetsTestRunner PROPERTIES
    FOLDER "Gadgets/TestRunner"
)

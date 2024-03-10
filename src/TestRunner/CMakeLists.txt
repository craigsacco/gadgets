add_gadgets_executable(GadgetsTestRunner
    #[[ALIAS]]      Gadgets::TestRunner
    #[[IDEFOLDER]]  "Gadgets/TestRunner"
)

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

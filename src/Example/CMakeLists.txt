add_gadgets_library(
    TARGET      GadgetsExample
    ALIAS       Gadgets::Example
    IDEFOLDER   "Gadgets/Example"
)

target_include_directories(GadgetsExample
    PRIVATE include
)

target_link_libraries(GadgetsExample
    PRIVATE Gadgets::Core
            Gadgets::Devices::DigitalOutput
            Gadgets::Drivers::EmulatedDigitalOutput
)

target_sources(GadgetsExample
    PUBLIC  src/main.cpp
)

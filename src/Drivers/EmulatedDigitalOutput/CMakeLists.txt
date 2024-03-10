add_gadgets_library(GadgetsDriversEmulatedDigitalOutput
    #[[ALIAS]]      Gadgets::Drivers::EmulatedDigitalOutput
    #[[IDEFOLDER]]  "Gadgets/Drivers"
)

target_include_directories(GadgetsDriversEmulatedDigitalOutput
    PUBLIC  include
    PRIVATE src
)

target_link_libraries(GadgetsDriversEmulatedDigitalOutput
    PUBLIC  Gadgets::Devices::DigitalOutput
            Gadgets::Drivers::Common
)

target_sources(GadgetsDriversEmulatedDigitalOutput
    PRIVATE src/EmulatedDigitalOutputDriver.cpp
            include/Gadgets/Drivers/EmulatedDigitalOutputDriver.hpp
)

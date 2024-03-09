add_library(GadgetsDriversEmulatedDigitalOutput)
add_library(Gadgets::Drivers::EmulatedDigitalOutput ALIAS GadgetsDriversEmulatedDigitalOutput)

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

set_target_properties(GadgetsDriversEmulatedDigitalOutput PROPERTIES
    FOLDER "Gadgets/Drivers"
)

add_library(GadgetsDevicesDigitalOutput)
add_library(Gadgets::Devices::DigitalOutput ALIAS GadgetsDevicesDigitalOutput)

target_include_directories(GadgetsDevicesDigitalOutput
    PUBLIC  include
    PRIVATE src
)

target_link_libraries(GadgetsDevicesDigitalOutput
    PUBLIC  Gadgets::Devices::Common
)

target_sources(GadgetsDevicesDigitalOutput
    PRIVATE src/DigitalOutputDevice.cpp
            include/Gadgets/Devices/DigitalOutputDevice.hpp
            include/Gadgets/Devices/IDigitalOutputDevice.hpp
            include/Gadgets/Devices/IDigitalOutputDriver.hpp
)

set_target_properties(GadgetsDevicesDigitalOutput PROPERTIES
    FOLDER "Gadgets/Devices"
)

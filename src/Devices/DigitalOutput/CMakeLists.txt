add_gadgets_library(
    TARGET      GadgetsDevicesDigitalOutput
    ALIAS       Gadgets::Devices::DigitalOutput
    IDEFOLDER   "Gadgets/Devices"
)

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

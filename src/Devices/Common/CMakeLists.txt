add_gadgets_library(
    TARGET      GadgetsDevicesCommon
    ALIAS       Gadgets::Devices::Common
    IDEFOLDER   "Gadgets/Devices"
)

target_include_directories(GadgetsDevicesCommon
    PUBLIC  include
    PRIVATE src
)

target_link_libraries(GadgetsDevicesCommon
    PUBLIC  Gadgets::Core
)

target_sources(GadgetsDevicesCommon
    PRIVATE src/BaseDevice.cpp
            include/Gadgets/Devices/BaseDevice.hpp
            include/Gadgets/Devices/DeviceResponse.hpp
            include/Gadgets/Devices/DriverResponse.hpp
            include/Gadgets/Devices/IDevice.hpp
            include/Gadgets/Devices/IDeviceDriver.hpp
)

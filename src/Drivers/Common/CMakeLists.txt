add_library(GadgetsDriversCommon)
add_library(Gadgets::Drivers::Common ALIAS GadgetsDriversCommon)

target_include_directories(GadgetsDriversCommon
    PUBLIC  include
    PRIVATE src
)

target_link_libraries(GadgetsDriversCommon
    PUBLIC  Gadgets::Core
            Gadgets::Devices::Common
)

target_sources(GadgetsDriversCommon
    PRIVATE src/BaseDeviceDriver.cpp
            include/Gadgets/Drivers/BaseDeviceDriver.hpp
)

set_target_properties(GadgetsDriversCommon PROPERTIES
    FOLDER "Gadgets/Drivers"
)

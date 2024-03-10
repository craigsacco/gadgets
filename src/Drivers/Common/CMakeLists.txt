add_gadgets_library(GadgetsDriversCommon
    #[[ALIAS]]      Gadgets::Drivers::Common
    #[[IDEFOLDER]]  "Gadgets/Drivers"
)

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

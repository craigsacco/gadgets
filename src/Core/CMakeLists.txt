add_library(GadgetsCore)
add_library(Gadgets::Core ALIAS GadgetsCore)

target_include_directories(GadgetsCore
    PUBLIC  include
    PRIVATE src
)

target_link_libraries(GadgetsCore
    PUBLIC  Boost::asio
)

target_sources(GadgetsCore
    PRIVATE src/Semaphore.cpp
            src/TaskQueue.cpp
            src/Thread.cpp
            include/Gadgets/Core/ITaskQueue.hpp
            include/Gadgets/Core/Semaphore.hpp
            include/Gadgets/Core/TaskQueue.hpp
            include/Gadgets/Core/Thread.hpp
)

set_target_properties(GadgetsCore PROPERTIES
    FOLDER "Gadgets/Core"
)
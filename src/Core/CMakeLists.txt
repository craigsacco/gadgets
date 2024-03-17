add_gadgets_library(
    TARGET      GadgetsCore
    ALIAS       Gadgets::Core
    IDEFOLDER   "Gadgets/Core"
)

target_include_directories(GadgetsCore
    PUBLIC  include
    PRIVATE src
)

target_link_libraries(GadgetsCore
    PUBLIC  Boost::asio
)

target_sources(GadgetsCore
    PRIVATE src/LoggerSingleton.cpp
            src/Semaphore.cpp
            src/TaskQueue.cpp
            src/Thread.cpp
            include/Gadgets/Core/AssertionMacros.hpp
            include/Gadgets/Core/CommonMacros.hpp
            include/Gadgets/Core/ExceptionMacros.hpp
            include/Gadgets/Core/ILogger.hpp
            include/Gadgets/Core/IObject.hpp
            include/Gadgets/Core/ITaskQueue.hpp
            include/Gadgets/Core/LoggerMacros.hpp
            include/Gadgets/Core/LoggerSingleton.hpp
            include/Gadgets/Core/Semaphore.hpp
            include/Gadgets/Core/Singleton.hpp
            include/Gadgets/Core/TaskQueue.hpp
            include/Gadgets/Core/Thread.hpp
)

# Copyright (c) 2024 Craig Sacco
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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
            include/Gadgets/Core/IThread.hpp
            include/Gadgets/Core/LoggerMacros.hpp
            include/Gadgets/Core/LoggerSingleton.hpp
            include/Gadgets/Core/Semaphore.hpp
            include/Gadgets/Core/Singleton.hpp
            include/Gadgets/Core/TaskQueue.hpp
            include/Gadgets/Core/Thread.hpp
)

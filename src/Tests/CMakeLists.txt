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

# SPDX-License-Identifier: MIT

add_gadgets_executable(
    TARGET      GadgetsTestRunner
    ALIAS       Gadgets::TestRunner
    IDEFOLDER   "Gadgets/Tests"
)

target_include_directories(GadgetsTestRunner
    PRIVATE include
)

target_link_libraries(GadgetsTestRunner
    PUBLIC  Gadgets::Core
            Gadgets::Devices::Common
            Gadgets::Devices::DigitalOutput
            Gadgets::Drivers::EmulatedDigitalOutput
            gmock
            gtest
)

target_sources(GadgetsTestRunner
    PRIVATE include/Gadgets/Core/MockLogger.hpp
            include/Gadgets/Core/MockTaskQueue.hpp
            include/Gadgets/Devices/MockDeviceDriver.hpp
            include/Gadgets/Devices/MockDigitalOutputDriver.hpp
            
            src/main.cpp
            src/Gadgets/Core/LoggerSingletonTests.cpp
            src/Gadgets/Core/SemaphoreTests.cpp
            src/Gadgets/Core/TaskQueueTests.cpp
            src/Gadgets/Devices/BaseDeviceTests.cpp
            src/Gadgets/Devices/DigitalOutputDeviceTests.cpp
            src/Gadgets/Drivers/EmulatedDigitalOutputDriverTests.cpp
)

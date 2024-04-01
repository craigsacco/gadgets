/*
 * Copyright (c) 2024 Craig Sacco
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// SPDX-License-Identifier: MIT

#include <Gadgets/Core/AssertionMacros.hpp>
#include <Gadgets/Core/ITaskQueue.hpp>
#include <Gadgets/Drivers/BaseDeviceDriver.hpp>

namespace Gadgets
{
namespace Drivers
{
BaseDeviceDriver::BaseDeviceDriver( const std::string& name, const std::string& type )
    : m_name( name )
    , m_type( type )
    , m_pTaskQueue( nullptr )
{
}

BaseDeviceDriver::~BaseDeviceDriver()
{
}

std::string
BaseDeviceDriver::Type() const
{
    return m_type;
}

std::string
BaseDeviceDriver::Name() const
{
    return m_name;
}

void
BaseDeviceDriver::SetTaskQueue( Core::ITaskQueueSPtr pTaskQueue )
{
    ASSERT_MSG( m_pTaskQueue == nullptr, "Task queue already set" );

    m_pTaskQueue = pTaskQueue;
}

Core::ITaskQueueSPtr
BaseDeviceDriver::GetTaskQueue() const
{
    ASSERT_MSG( m_pTaskQueue != nullptr, "Task queue not set" );

    return m_pTaskQueue;
}
} // namespace Drivers
} // namespace Gadgets
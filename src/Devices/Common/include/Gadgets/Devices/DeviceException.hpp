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

#pragma once

#include <Gadgets/Devices/DeviceResponse.hpp>

#include <stdexcept>

namespace Gadgets
{
namespace Devices
{

/**
 * @brief   Exception class for device errors.
 */
class DeviceException : public std::exception
{
public:
    /**
     * @brief       Constructor for this exception.
     *
     * @param[in]   message     The message to attached to the exception.
     * @param[in]   response    The device response code.
     */
    DeviceException( const std::string& message, DeviceResponse response )
        : std::exception()
        , m_message( message )
        , m_response( response )
    {
    }

    /**
     * @brief       Virtual destructor.
     */
    virtual ~DeviceException();

    /**
     * @brief       Gets the message attached to this exception.
     *
     * @return      The message string.
     */
    const char*
    what() const noexcept override
    {
        return m_message.c_str();
    }

    /**
     * @brief       Gets the message attached to this exception.
     *
     * @return      The message string.
     */
    std::string
    GetMessage() const
    {
        return m_message;
    }

    /**
     * @brief       Gets the response code attached to this exception.
     *
     * @return      The response code.
     */
    DeviceResponse
    GetResponse() const
    {
        return m_response;
    }

private:
    std::string m_message;
    DeviceResponse m_response;
};

} // namespace Devices
} // namespace Gadgets

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

#include <Gadgets/Core/LoggerMacros.hpp>
#include <Gadgets/Core/LoggerSingleton.hpp>
#include <Gadgets/Core/TaskQueue.hpp>
#include <Gadgets/Devices/DigitalOutputDevice.hpp>
#include <Gadgets/Drivers/EmulatedDigitalOutputDriver.hpp>

void
testTaskQueue()
{
    LOG_INFO( "Testing the task queue" );

    auto pTaskQueue = std::make_shared<Gadgets::Core::TaskQueue>( "main" );

    pTaskQueue->Start();

    for ( int i = 0; i < 50; i++ )
    {
        pTaskQueue->BeginInvoke(
            [ /*i*/ ]
            {
                // LOG_INFO("%i\n", i);
            } );
    }

    pTaskQueue->Stop();
}

void
testDeviceAndDriverInfrastructure()
{
    printf( "Testing the driver infrastructure\n\n" );

    auto pTaskQueue = std::make_shared<Gadgets::Core::TaskQueue>( "main" );

    printf( "Starting\n" );
    pTaskQueue->Start();
    printf( "Started\n" );

    auto pDriver =
        std::make_shared<Gadgets::Drivers::EmulatedDigitalOutputDriver>( "EmulatedOutput" );
    pDriver->SetTaskQueue( pTaskQueue );
    auto pDevice = std::make_shared<Gadgets::Devices::DigitalOutputDevice>( "Output", pDriver );

    printf( "Initialise device\n" );
    pDevice->Initialise();
    pDevice->Wait();

    printf( "Initial GetState: %d\n", pDevice->GetState() );
    pDevice->On();
    pDevice->Wait();
    printf( "GetState: %d\n", pDevice->GetState() );
    pDevice->Off();
    pDevice->Wait();
    printf( "GetState: %d\n", pDevice->GetState() );
    pDevice->SetState( true );
    pDevice->Wait();
    printf( "GetState: %d\n", pDevice->GetState() );
    pDevice->SetState( false );
    pDevice->Wait();
    printf( "GetState: %d\n", pDevice->GetState() );

    printf( "Shutdown device\n" );
    pDevice->Shutdown();
    pDevice->Wait();

    printf( "Stopping\n" );
    pTaskQueue->Stop();
    printf( "Stopped\n" );
}

int
main( int argc, char** argv )
{
    ( void )argc;
    ( void )argv;

    Gadgets::Core::LoggerSingleton::Get();

    testTaskQueue();
    // testDeviceAndDriverInfrastructure();

    Gadgets::Core::LoggerSingleton::Destroy();

    return 0;
}

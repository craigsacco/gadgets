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
        pTaskQueue->Enqueue( [ i ] {
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

    auto pDriver = std::make_shared<Gadgets::Drivers::EmulatedDigitalOutputDriver>( "EmulatedOutput" );
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
    (void)argc;
    (void)argv;

    Gadgets::Core::LoggerSingleton::Get();

    testTaskQueue();
    // testDeviceAndDriverInfrastructure();

    Gadgets::Core::LoggerSingleton::Destroy();

    return 0;
}

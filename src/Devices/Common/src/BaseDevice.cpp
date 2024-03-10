

#include <Gadgets/Core/ExceptionMacros.hpp>
#include <Gadgets/Core/ITaskQueue.hpp>
#include <Gadgets/Devices/BaseDevice.hpp>
#include <Gadgets/Devices/IDeviceDriver.hpp>

#include <map>

namespace Gadgets
{
    namespace Devices
    {
        BaseDevice::BaseDevice( const std::string& name, const std::string& type, IDeviceDriverSPtr pDriver )
            : m_name( name ), m_type( type ), m_pDriver( pDriver ), m_semaphore()
        {
        }

        BaseDevice::~BaseDevice() {}

        std::string
        BaseDevice::Name() const
        {
            return m_name;
        }

        void
        BaseDevice::Initialise()
        {
            StartAsyncAction();

            m_pDriver->GetTaskQueue()->Enqueue( [ this ] {
                m_pDriver->Initialise(
                    [ this ]( DriverResponse response ) { FinaliseAsyncAction( ToDeviceResponse( response ) ); } );
            } );
        }

        void
        BaseDevice::Shutdown()
        {
            StartAsyncAction();

            m_pDriver->GetTaskQueue()->Enqueue( [ this ] {
                m_pDriver->Shutdown(
                    [ this ]( DriverResponse response ) { FinaliseAsyncAction( ToDeviceResponse( response ) ); } );
            } );
        }

        void
        BaseDevice::Wait()
        {
            Wait( DefaultTimeout() );
        }

        void
        BaseDevice::Wait( std::chrono::milliseconds timeout_ms )
        {
            if ( !m_semaphore.Wait( timeout_ms ) )
            {
                THROW_RUNTIME_ERROR( "Action timed out" );
            }
        }

        std::string
        BaseDevice::Type() const
        {
            return m_type;
        }

        std::chrono::milliseconds
        BaseDevice::DefaultTimeout() const
        {
            return std::chrono::milliseconds( 2000 );
        }

        void
        BaseDevice::StartAsyncAction()
        {
            if ( !m_semaphore.Acquire() )
            {
                THROW_RUNTIME_ERROR( "Device is busy" );
            }
        }

        void
        BaseDevice::FinaliseAsyncAction( DeviceResponse response )
        {
            if ( !m_semaphore.Release() )
            {
                THROW_LOGIC_ERROR( "StartAsyncAction() not called beforehand" );
            }
        }

        DeviceResponse
        BaseDevice::ToDeviceResponse( DriverResponse response ) const
        {
            static const std::map<DriverResponse, DeviceResponse> responseMap = {
                std::make_pair( StandardDriverResponses::DriverOK, StandardDeviceResponses::DeviceOK ),
                std::make_pair( StandardDriverResponses::DriverFailed, StandardDeviceResponses::DeviceFailed ),
            };

            if ( responseMap.find( response ) != responseMap.end() )
            {
                return responseMap.at( response );
            }

            return StandardDeviceResponses::DeviceFailed;
        }
    } // namespace Devices
} // namespace Gadgets
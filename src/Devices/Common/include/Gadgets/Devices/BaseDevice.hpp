

#pragma once

#include <Gadgets/Core/Semaphore.hpp>
#include <Gadgets/Devices/DriverResponse.hpp>
#include <Gadgets/Devices/IDevice.hpp>

#include <memory>

namespace Gadgets
{
namespace Devices
{
class IDeviceDriver;
using IDeviceDriverSPtr = std::shared_ptr<IDeviceDriver>;

class BaseDevice : public virtual IDevice
{
public:
    BaseDevice( const std::string& name, const std::string& type, IDeviceDriverSPtr pDriver );
    virtual ~BaseDevice();

    // overrides from IObject
    std::string Name() const override final;

    // overrides from IDevice
    void Initialise() override final;
    void Shutdown() override final;
    void Wait() override final;
    void Wait( std::chrono::milliseconds timeout_ms ) override final;
    std::string Type() const override final;

    std::chrono::milliseconds DefaultTimeout() const;

protected:
    void StartAsyncAction();
    void FinaliseAsyncAction( DeviceResponse response );
    virtual DeviceResponse ToDeviceResponse( DriverResponse response ) const;
    virtual void ResponseThrowOnError( DeviceResponse response ) const;

private:
    const std::string m_name;
    const std::string m_type;
    IDeviceDriverSPtr m_pDriver;
    Gadgets::Core::Semaphore m_semaphore;
};
} // namespace Devices
} // namespace Gadgets
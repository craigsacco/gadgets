

#include <Gadgets/Devices/DigitalOutputDevice.hpp>
#include <Gadgets/Devices/IDigitalOutputDriver.hpp>
#include <Gadgets/Core/ITaskQueue.hpp>

namespace Gadgets
{
	namespace Devices
	{
		DigitalOutputDevice::DigitalOutputDevice(const std::string& name, IDigitalOutputDriverSPtr pDriver)
			: BaseDevice(name, "DigitalOutput", pDriver)
			, m_pDriver(pDriver)
		{
		}

		DigitalOutputDevice::~DigitalOutputDevice()
		{
		}

		void DigitalOutputDevice::On()
		{
			StartAsyncAction();

			m_pDriver->GetTaskQueue()->Enqueue([this] {
				m_pDriver->On([this](DriverResponse response) {
					FinaliseAsyncAction(ToDeviceResponse(response));
					});
				});
		}

		void DigitalOutputDevice::Off()
		{
			StartAsyncAction();

			m_pDriver->GetTaskQueue()->Enqueue([this] {
				m_pDriver->Off([this](DriverResponse response) {
					FinaliseAsyncAction(ToDeviceResponse(response));
					});
				});
		}

		void DigitalOutputDevice::SetState(bool state)
		{
			StartAsyncAction();

			m_pDriver->GetTaskQueue()->Enqueue([this, state] {
				m_pDriver->SetState(state, [this](DriverResponse response) {
					FinaliseAsyncAction(ToDeviceResponse(response));
					});
				});
		}

		bool DigitalOutputDevice::GetState()
		{
			bool state = false;

			StartAsyncAction();

			m_pDriver->GetTaskQueue()->Enqueue([this, &state] {
				m_pDriver->GetState([this, &state](DriverResponse response, bool returnState) {
					state = returnState;
					FinaliseAsyncAction(ToDeviceResponse(response));
					});
				});

			Wait();
			return state;
		}

		DeviceResponse DigitalOutputDevice::ToDeviceResponse(DriverResponse response) const
		{
			return BaseDevice::ToDeviceResponse(response);
		}
	}
}
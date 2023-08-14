#pragma once

#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <functiondiscoverykeys.h>

#include <Base.h>

namespace Media {

	enum class DataFlow { Render, Capture, All };

	class Device
	{
	public:
		Device(size_t nDevice = 0, DataFlow df = DataFlow::Render);
		Device(const std::wstring& deviceID);
		~Device() = default;

		std::wstring GetDeviceName();
		IAudioClient* Activate();

	private:
		IMMDevice* GetDevicePointer(const size_t nDevice, const DataFlow df) const;
		IMMDevice* GetDevicePointer(const std::wstring& deviceID) const;
		
		COMScope<IMMDevice> m_pDevice;
	};
}
#pragma once

#include <Media/NotificationClient.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>

#include <Base.h>

namespace Media {

	enum class DataFlow { Render, Capture, All };

	class Device
	{
	public:
		Device(size_t nDevice = 0);
		Device(const std::wstring& deviceID);
		~Device() = default;

		std::wstring GetDeviceName();
		IAudioClient* Activate();

	private:
		COMScope<IMMDevice> m_pDevice;
	};

} // namespace Media
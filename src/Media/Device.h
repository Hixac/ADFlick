#pragma once

#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <Media/Notify/NotificationClient.h>

#include <Base.h>

namespace Media {

	enum class DataFlow { Render, Capture, All };

	class Device
	{
	public:
		Device(size_t nDevice = 0);
		Device(const std::wstring& deviceID);
		~Device() = default;

		IAudioClient* Activate();

		std::wstring GetDeviceName();
	private:
		COMScope<IMMDevice> m_pDevice;
	};

} // namespace Media
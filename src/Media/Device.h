#pragma once

#include <Media/Notify/NotificationClient.h>
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

		template<typename T>
		T* Activate(REFIID riid);

		std::wstring GetDeviceName();
	private:
		COMScope<IMMDevice> m_pDevice;
	};

} // namespace Media
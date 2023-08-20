#pragma once

#include <Media/Notify/NotificationClient.h>
#include <mmdeviceapi.h>

#include <Base.h>

namespace Media {

	class DeviceEnumerator
	{
	public:
		static DeviceEnumerator& Instance() { static DeviceEnumerator instance; return instance; }

		IMMDevice* GetDevicePointer(const std::wstring deviceID);
		IMMDevice* GetDevicePointer(const size_t nDevice);
		IMMDevice* GetDevicePointerFromCollection(const size_t nDevice);

		void RegisterCallback();
		void UnregisterCallback();

	private:
		COMScope<IMMDeviceEnumerator> GetEnumeratorPointer();
		COMScope<IMMDeviceCollection> GetCollectionPointer();

		COMScope<IMMDeviceCollection> m_pCollection;
		COMScope<IMMDeviceEnumerator> m_pEnumerator;

		DeviceEnumerator()										= default;
		~DeviceEnumerator()										= default;
		DeviceEnumerator(DeviceEnumerator const&)				= delete;
		DeviceEnumerator& operator=(DeviceEnumerator const&)	= delete;
	};

} // namespace Media
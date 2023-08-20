#include <Media/DeviceEnumerator.h>

namespace Media {

	IMMDevice* DeviceEnumerator::GetDevicePointer(const std::wstring deviceID)
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		IMMDevice* pDevice;
		CHECK(hr = GetEnumeratorPointer()->GetDevice(deviceID.c_str(), &pDevice));

		return pDevice;
	}

	IMMDevice* DeviceEnumerator::GetDevicePointer(const size_t nDevice)
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		IMMDevice* pDevice;
		CHECK(hr = GetCollectionPointer()->Item(nDevice, &pDevice));

		return pDevice;
	}

	IMMDevice* DeviceEnumerator::GetDevicePointerFromCollection(const size_t nDevice)
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		IMMDevice* pDevice;
		CHECK(hr = GetCollectionPointer()->Item(nDevice, &pDevice));

		return pDevice;
	}

	void DeviceEnumerator::RegisterCallback()
	{
		HRESULT hr = GetEnumeratorPointer()->RegisterEndpointNotificationCallback(&NotificationClient::GetNotifyInstance());
		CHECK(hr);
	}

	void DeviceEnumerator::UnregisterCallback()
	{
		HRESULT hr = GetEnumeratorPointer()->UnregisterEndpointNotificationCallback(&NotificationClient::GetNotifyInstance());
		CHECK(hr);
	}

	COMScope<IMMDeviceEnumerator> DeviceEnumerator::GetEnumeratorPointer()
	{
		if (m_pEnumerator.Get() == nullptr)
		{
			HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

			const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
			const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
			CHECK(hr = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL,
				CLSCTX_ALL, IID_IMMDeviceEnumerator,
				(void**)m_pEnumerator.GetAddressOf()));
		}
		return m_pEnumerator;
	}

	COMScope<IMMDeviceCollection> DeviceEnumerator::GetCollectionPointer()
	{
		if (m_pCollection.Get() == nullptr)
		{
			GetEnumeratorPointer()->EnumAudioEndpoints(eAll, DEVICE_STATE_ACTIVE, m_pCollection.GetAddressOf());
		}
		return m_pCollection;
	}

} // namespace Media
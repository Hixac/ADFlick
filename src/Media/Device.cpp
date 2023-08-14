#include <Media/Device.h>

namespace Media {

	Device::Device(size_t nDevice, DataFlow df)
	{
		m_pDevice = COMScope<IMMDevice>(GetDevicePointer(nDevice, df));
	}

	Device::Device(const std::wstring& deviceID)
	{
		m_pDevice = COMScope<IMMDevice>(GetDevicePointer(deviceID));
	}

	std::wstring Device::GetDeviceName()
	{
		LPWSTR deviceId;
		HRESULT hr = m_pDevice->GetId(&deviceId);

		IPropertyStore* propStore;
		CHECK(hr = m_pDevice->OpenPropertyStore(STGM_READ, &propStore));

		PROPVARIANT varName;
		PropVariantInit(&varName);

		CHECK(hr = propStore->GetValue(PKEY_Device_FriendlyName, &varName));

		SAFE_RELEASE(propStore);

		if (varName.vt != VT_EMPTY)
		{
			return varName.pwszVal;
		}
	}

	IAudioClient* Device::Activate()
	{
		IAudioClient* pAudioClient;
		m_pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, reinterpret_cast<void**>(&pAudioClient));

		return pAudioClient;
	}

	IMMDevice* Device::GetDevicePointer(const size_t nDevice, const DataFlow df) const
	{
		IMMDeviceEnumerator* pEnumerator;
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
		const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
		CHECK(hr = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL,
			CLSCTX_ALL, IID_IMMDeviceEnumerator,
			reinterpret_cast<void**>(&pEnumerator)));

		IMMDeviceCollection* pCollection;
		CHECK(hr = pEnumerator->EnumAudioEndpoints((EDataFlow)df, DEVICE_STATE_ACTIVE, &pCollection));

		IMMDevice* pDevice;
		CHECK(hr = pCollection->Item(nDevice, &pDevice));

		SAFE_RELEASE(pEnumerator);
		SAFE_RELEASE(pCollection);

		return pDevice;
	}

	IMMDevice* Device::GetDevicePointer(const std::wstring& deviceID) const
	{
		IMMDeviceEnumerator* pEnumerator;
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
		const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
		CHECK(hr = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL,
			CLSCTX_ALL, IID_IMMDeviceEnumerator,
			reinterpret_cast<void**>(&pEnumerator)));

		IMMDevice* pDevice;
		CHECK(hr = pEnumerator->GetDevice(reinterpret_cast<LPCWSTR>(&deviceID), &pDevice));

		SAFE_RELEASE(pEnumerator)

		return pDevice;
	}
}
#include <Media/Device.h>
#include <Media/DeviceEnumerator.h>

#include <functiondiscoverykeys.h>

namespace Media {

	Device::Device(size_t nDevice)
	{
		m_pDevice = COMScope<IMMDevice>(DeviceEnumerator::Instance().GetDevicePointer(nDevice));
	}

	Device::Device(const std::wstring& deviceID)
	{
		m_pDevice = COMScope<IMMDevice>(DeviceEnumerator::Instance().GetDevicePointer(deviceID));
	}

	std::wstring Device::GetDeviceName()
	{
		IPropertyStore* propStore;
		HRESULT hr = m_pDevice->OpenPropertyStore(STGM_READ, &propStore);
		CHECK(hr);

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
		IAudioClient* pHolder;
		m_pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, reinterpret_cast<void**>(&pHolder));

		return pHolder;
	}

} // namespace Media
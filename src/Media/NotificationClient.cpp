#include <Media/NotificationClient.h>

#include <Media/Device.h>

namespace Media {

	NotificationClient::~NotificationClient()
	{
		Release();
	}

	HRESULT STDMETHODCALLTYPE NotificationClient::QueryInterface(REFIID riid, void** ppvInterface)
	{
		if (IID_IUnknown == riid)
		{
			AddRef();
			*ppvInterface = reinterpret_cast<IUnknown*>(this);
		}
		else if (__uuidof(IMMNotificationClient) == riid)
		{
			AddRef();
			*ppvInterface = reinterpret_cast<IMMNotificationClient*>(this);
		}
		else
		{
			*ppvInterface = nullptr;
			return E_NOINTERFACE;
		}
		return S_OK;
	}

	unsigned long __stdcall NotificationClient::AddRef(void)
	{
		return InterlockedIncrement(&m_CountRef);
	}

	unsigned long __stdcall NotificationClient::Release(void)
	{
		unsigned long ulRef = InterlockedDecrement(&m_CountRef);
		if (0 == ulRef)
		{
			delete this;
		}
		return ulRef;
	}

	HRESULT __stdcall NotificationClient::OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState)
	{
		std::wstring ws(pwstrDeviceId);
		Device device(ws);
		
		std::wstring out = device.GetDeviceName();
		switch (dwNewState)
		{
		case DEVICE_STATE_ACTIVE:
			out += L" new device state is ACTIVE";
			break;
		case DEVICE_STATE_DISABLED:
			out += L" new device state is DISABLED";
			break;
		case DEVICE_STATE_NOTPRESENT:
			out += L" new device state is NOTPRESENT";
			break;
		case DEVICE_STATE_UNPLUGGED:
			out += L" new device state is UNPLUGGED";
			break;
		}

		LOG_INFO(out);

		return S_OK;
	}

	HRESULT __stdcall NotificationClient::OnDeviceAdded(LPCWSTR pwstrDeviceId)
	{
		std::wstring ws(pwstrDeviceId);
		Device device(ws);

		std::wstring out = device.GetDeviceName() + L" has been added!";
		LOG_INFO(out);
		
		return S_OK;
	}

	HRESULT __stdcall NotificationClient::OnDeviceRemoved(LPCWSTR pwstrDeviceId)
	{
		std::wstring ws(pwstrDeviceId);
		Device device(ws);

		std::wstring out = device.GetDeviceName() + L" has been removed!";
		LOG_INFO(out);

		return S_OK;
	}

	HRESULT __stdcall NotificationClient::OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDefaultDeviceId)
	{
		std::wstring ws(pwstrDefaultDeviceId);
		Device device(ws);

		std::wstring out = device.GetDeviceName();

		switch (flow)
		{
		case eRender:
			out += L" - eRender";
			break;
		case eCapture:
			out += L" - eCapture";
			break;
		}

		switch (role)
		{
		case eConsole:
			out += L" - eConsole";
			break;
		case eMultimedia:
			out += L" - eMultimedia";
			break;
		case eCommunications:
			out += L" - eCommunications";
			break;
		}

		LOG_INFO(out + L": is new default device!");

		return S_OK;
	}

	HRESULT __stdcall NotificationClient::OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key)
	{
		return E_NOTIMPL;
	}
}
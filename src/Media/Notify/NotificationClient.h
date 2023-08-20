#pragma once

#include <mmdeviceapi.h>
#include <Base.h>

namespace Media {

	class NotificationClient : public IMMNotificationClient
	{
	public:
		static NotificationClient& GetNotifyInstance() { static NotificationClient instance; return instance; }

		// IUnknown
		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvInterface) override;

		unsigned long STDMETHODCALLTYPE AddRef(void) override;
		unsigned long STDMETHODCALLTYPE Release(void) override;

		// IMMNotificationClient
		HRESULT __stdcall OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState) override;
		HRESULT __stdcall OnDeviceAdded(LPCWSTR pwstrDeviceId) override;
		HRESULT __stdcall OnDeviceRemoved(LPCWSTR pwstrDeviceId) override;
		HRESULT __stdcall OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDefaultDeviceId) override;
		HRESULT __stdcall OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key) override;

	private:
		NotificationClient() : m_CountRef(1) { }
		~NotificationClient();

		NotificationClient(NotificationClient const&)				= delete;
		NotificationClient& operator=(NotificationClient const&)	= delete;

		size_t m_CountRef;
	};

}
#pragma once

#include <Base.h>
#include <Media/Device.h>

namespace Media {

	class NotificationClient : public IMMNotificationClient
	{
	public:
		NotificationClient() : m_CountRef(1), m_pEnumerator(nullptr) { }
		~NotificationClient() = default;

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
		size_t m_CountRef;
		COMScope<IMMDeviceEnumerator> m_pEnumerator;
	};

}
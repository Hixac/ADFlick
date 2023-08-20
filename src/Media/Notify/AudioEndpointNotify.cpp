#include <Media/Notify/AudioEndpointNotify.h>

#include <Base.h>

namespace Media {

	AudioEndpointVolumeCallBack::~AudioEndpointVolumeCallBack()
	{
		Release();
	}

	HRESULT __stdcall AudioEndpointVolumeCallBack::QueryInterface(REFIID riid, void** ppvObject)
	{
		if (IID_IUnknown == riid)
		{
			AddRef();
			*ppvObject = reinterpret_cast<IUnknown*>(this);
		}
		else if (__uuidof(IAudioEndpointVolumeCallback) == riid)
		{
			AddRef();
			*ppvObject = reinterpret_cast<IAudioEndpointVolumeCallback*>(this);
		}
		else
		{
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}
		return S_OK;
	}

	ULONG __stdcall AudioEndpointVolumeCallBack::AddRef(void)
	{
		return InterlockedIncrement(&m_CountRef);
	}

	ULONG __stdcall AudioEndpointVolumeCallBack::Release(void)
	{
		ULONG ulRef = InterlockedDecrement(&m_CountRef);
		if (0 == ulRef)
		{
			delete this;
		}
		return ulRef;
	}

	HRESULT __stdcall AudioEndpointVolumeCallBack::OnNotify(PAUDIO_VOLUME_NOTIFICATION_DATA pNotify)
	{
		if (pNotify->bMuted)
		{
			LOG_INFO("Endpoint device got muted!");
		}
		return S_OK;
	}

} // namespace Media
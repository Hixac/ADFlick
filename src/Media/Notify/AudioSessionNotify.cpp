#include <Media/Notify/AudioSessionNotify.h>

#include <Base.h>

namespace Media {

	AudioSessionNotify::~AudioSessionNotify()
	{
		Release();
	}

	HRESULT __stdcall AudioSessionNotify::QueryInterface(REFIID riid, void** ppvObject)
	{
		if (IID_IUnknown == riid)
		{
			AddRef();
			*ppvObject = reinterpret_cast<IUnknown*>(this);
		}
		else if (__uuidof(IAudioSessionEvents) == riid)
		{
			AddRef();
			*ppvObject = reinterpret_cast<IAudioSessionEvents*>(this);
		}
		else
		{
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}
		return S_OK;
	}

	ULONG __stdcall AudioSessionNotify::AddRef(void)
	{
		return InterlockedIncrement(&m_CountRef);
	}

	ULONG __stdcall AudioSessionNotify::Release(void)
	{
		unsigned long ulRef = InterlockedDecrement(&m_CountRef);
		if (0 == ulRef)
		{
			delete this;
		}
		return ulRef;
	}

	HRESULT __stdcall AudioSessionNotify::OnDisplayNameChanged(LPCWSTR NewDisplayName, LPCGUID EventContext)
	{
		std::wstring ws(NewDisplayName);
		LOG_INFO(L"New audio session display name -> " + ws);

		return S_OK;
	}

	HRESULT __stdcall AudioSessionNotify::OnIconPathChanged(LPCWSTR NewIconPath, LPCGUID EventContext)
	{
		std::wstring ws(NewIconPath);
		LOG_INFO(L"New audio session display name -> " + ws);

		return S_OK;
	}

	HRESULT __stdcall AudioSessionNotify::OnSimpleVolumeChanged(float NewVolume, BOOL NewMute, LPCGUID EventContext)
	{
		if (NewMute)
			LOG_INFO("Audio session is on mute!");
		else 
		{
			LOG_INFO("Audio session volume changed -> " + std::to_string(100 * NewVolume + 0.5f));
		}

		return S_OK;
	}

	HRESULT __stdcall AudioSessionNotify::OnChannelVolumeChanged(DWORD ChannelCount, float NewChannelVolumeArray[], DWORD ChangedChannel, LPCGUID EventContext)
	{
		return S_OK;
	}

	HRESULT __stdcall AudioSessionNotify::OnGroupingParamChanged(LPCGUID NewGroupingParam, LPCGUID EventContext)
	{
		return S_OK;
	}

	HRESULT __stdcall AudioSessionNotify::OnStateChanged(AudioSessionState NewState)
	{
		std::string out;

		switch (NewState)
		{
		case AudioSessionStateActive:
			out = "active";
			break;
		case AudioSessionStateInactive:
			out = "inactive";
			break;
		}

		LOG_INFO("Audio state changed -> " + out);

		return S_OK;
	}

	HRESULT __stdcall AudioSessionNotify::OnSessionDisconnected(AudioSessionDisconnectReason DisconnectReason)
	{
		std::string out;

		switch (DisconnectReason)
		{
		case DisconnectReasonDeviceRemoval:
			out = "device removed";
			break;
		case DisconnectReasonServerShutdown:
			out = "server shut down";
			break;
		case DisconnectReasonFormatChanged:
			out = "format changed";
			break;
		case DisconnectReasonSessionLogoff:
			out = "user logged off";
			break;
		case DisconnectReasonSessionDisconnected:
			out = "session disconnected";
			break;
		case DisconnectReasonExclusiveModeOverride:
			out = "exclusive-mode override";
			break;
		}
		
		LOG_INFO("Audio session: " + out);

		return S_OK;
	}

} // namespace Media
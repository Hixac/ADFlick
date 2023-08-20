#pragma once

#include <audiopolicy.h>

namespace Media {

	class AudioSessionNotify : public IAudioSessionEvents
	{
	public:
		static AudioSessionNotify& GetNotifyInstance() { static AudioSessionNotify instance; return instance; }

		// IUnknown
		HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		ULONG __stdcall AddRef(void) override;
		ULONG __stdcall Release(void) override;

		// IAudioSessionEvents
		HRESULT __stdcall OnDisplayNameChanged(LPCWSTR NewDisplayName, LPCGUID EventContext) override;
		HRESULT __stdcall OnIconPathChanged(LPCWSTR NewIconPath, LPCGUID EventContext) override;
		HRESULT __stdcall OnSimpleVolumeChanged(float NewVolume, BOOL NewMute, LPCGUID EventContext) override;
		HRESULT __stdcall OnChannelVolumeChanged(DWORD ChannelCount, float NewChannelVolumeArray[], DWORD ChangedChannel, LPCGUID EventContext) override;
		HRESULT __stdcall OnGroupingParamChanged(LPCGUID NewGroupingParam, LPCGUID EventContext) override;
		HRESULT __stdcall OnStateChanged(AudioSessionState NewState) override;
		HRESULT __stdcall OnSessionDisconnected(AudioSessionDisconnectReason DisconnectReason) override;

	private:
		AudioSessionNotify() : m_CountRef(1) { }
		~AudioSessionNotify();

		AudioSessionNotify(AudioSessionNotify const&)				= delete;
		AudioSessionNotify& operator=(AudioSessionNotify const&)	= delete;

		size_t m_CountRef;
	};

} // namespace Media
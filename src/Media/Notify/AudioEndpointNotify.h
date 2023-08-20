#pragma once

#include <endpointvolume.h>

namespace Media {

	class AudioEndpointVolumeCallBack : public IAudioEndpointVolumeCallback
	{
	public:
		static AudioEndpointVolumeCallBack& Instance() { static AudioEndpointVolumeCallBack instance; return instance; }

		// IUnknown
		HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		ULONG __stdcall AddRef(void) override;
		ULONG __stdcall Release(void) override;

		// IAudioEndpointVolumeCallback
		HRESULT __stdcall OnNotify(PAUDIO_VOLUME_NOTIFICATION_DATA pNotify) override;

	private:
		AudioEndpointVolumeCallBack() : m_CountRef(1) { }
		~AudioEndpointVolumeCallBack();

		AudioEndpointVolumeCallBack(AudioEndpointVolumeCallBack const&)				= delete;
		AudioEndpointVolumeCallBack& operator=(AudioEndpointVolumeCallBack const&)	= delete;

		size_t m_CountRef;
	};

} // namespace Media
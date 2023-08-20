#pragma once

#include <Media/Device.h>
#include <Media/Volume.h>
#include <AudioClient.h>

namespace Media {

	enum class ShareMode { Shared = 0, Exclusive };

	enum class StreamFlags : unsigned long
	{
		CrossProcess =		0x00010000, 
		EventCallback =		0x00040000, 
		LoopBack =			0x00020000,
		NoPersist =			0x00080000,
		RateAdjust =		0x00100000, 
		SourceQuality =		0x08000000,
		AutoConvertPCM =	0x80000000,
	};

	using tick_t = int64_t;
	using Wave = WAVEFORMATEX;

	class AudioClient
	{
	public:
		AudioClient(Device& device);
		~AudioClient() = default;

		void Initialize(ShareMode mode, StreamFlags flags, const Wave* pFormat, tick_t bufferDuration, tick_t periodicity = 0);

		uint32_t GetBufferSize();
		uint32_t GetCurrentPadding();
		tick_t GetDefaultDevicePeriod();
		tick_t GetMinimumDevicePeriod();
		tick_t GetStreamLatency();
		Wave* GetMixFormat();

		Wave* FormatSupported(ShareMode mode, const Wave* pFormat);

		void Start();
		void Stop();
		void Reset();

		void SetEventHandle();

		template<typename T>
		T* GetService(REFIID riid);

	private:
		GUID m_Session;

		Scope<Device> m_pDevice;
		COMScope<IAudioClient> m_pAudioClient;
	};

} // namespace Media
#include <Media/AudioClient.h>

namespace Media {

    AudioClient::AudioClient(Device& device)
        : m_Session(GUID_NULL), m_pDevice(CreateScope<Device>(device))
    {
        IAudioClient* pClient = m_pDevice->Activate();
        m_pAudioClient = COMScope<IAudioClient>(pClient);
    }

    void AudioClient::Initialize(ShareMode mode, StreamFlags flags, const Wave* pFormat, tick_t bufferDuration, tick_t periodicity)
    {
        CHECK(m_pAudioClient->Initialize((AUDCLNT_SHAREMODE)mode, (DWORD)flags, bufferDuration, periodicity, pFormat, &m_Session));
    }

    uint32_t AudioClient::GetBufferSize()
    {
        uint32_t bufferSize;
        CHECK(m_pAudioClient->GetBufferSize(&bufferSize));

        return bufferSize;
    }

    uint32_t AudioClient::GetCurrentPadding()
    {
        uint32_t currentPadding;
        CHECK(m_pAudioClient->GetCurrentPadding(&currentPadding));

        return currentPadding;
    }

    tick_t AudioClient::GetDefaultDevicePeriod()
    {
        tick_t defaultDevicePeriod;
        CHECK(m_pAudioClient->GetDevicePeriod(&defaultDevicePeriod, nullptr));

        return defaultDevicePeriod;
    }

    tick_t AudioClient::GetMinimumDevicePeriod()
    {
        tick_t minimumDevicePeriod;
        CHECK(m_pAudioClient->GetDevicePeriod(nullptr, &minimumDevicePeriod));

        return minimumDevicePeriod;
    }

    tick_t AudioClient::GetStreamLatency()
    {
        tick_t latency;
        CHECK(m_pAudioClient->GetStreamLatency(&latency));

        return latency;
    }

    Wave* AudioClient::GetMixFormat()
    {
        Wave* format;
        CHECK(m_pAudioClient->GetMixFormat(&format));

        return format;
    }

    Wave* AudioClient::FormatSupported(ShareMode mode, const Wave* pFormat)
    {
        Wave* format;
        CHECK(m_pAudioClient->IsFormatSupported((AUDCLNT_SHAREMODE)mode, pFormat, &format));

        return format;
    }

    void AudioClient::Start()
    {
        CHECK(m_pAudioClient->Start());
    }

    void AudioClient::Stop()
    {
        CHECK(m_pAudioClient->Stop());
    }

    void AudioClient::Reset()
    {
        CHECK(m_pAudioClient->Reset());
    }

    void AudioClient::SetEventHandle()
    {
        HANDLE hEvent = CreateEvent(NULL, false, false, NULL);
        CHECK(m_pAudioClient->SetEventHandle(hEvent));
    }

    template<typename T>
    T* AudioClient::GetService(REFIID riid)
    {
        T* pService;
        CHECK(m_pAudioClient->GetService(riid, reinterpret_cast<void**>(pService)));

        return pService;
    }

} // namespace Media
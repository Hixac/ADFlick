#pragma once

#include <Media/Device.h>
#include <AudioClient.h>

namespace Media {

	enum class SessionState
	{
		Active = 0, // Running state
		Inactive, 	// Stopped state
		Expired		// After a session has been inactive for a period of time, the system changes the state of the session from inactive to expired.
	};

	class AudioSession
	{
	public:
		AudioSession(IMMDevice* device);

	private:
		COMScope<IAudioClient> m_pAudioClient;
	};

} // namespace Media
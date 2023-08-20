#pragma once

#include <Media/Device.h>
#include <Media/AudioClient.h>
#include <Base.h>

namespace Media {

	template<typename T>
	class Service
	{
	public:
		Service(AudioClient& audioClient);
		Service(Device& device);

		T GetService() const;

	private:
		COMScope<T> m_pService;
	};

} // namespace Media
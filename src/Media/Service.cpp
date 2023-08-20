#include <Media/Service.h>

namespace Media {

	template<typename T>
	Service<T>::Service(AudioClient& audioClient)
	{
		m_pService = audioClient.GetService<T>(__uuidof(T));
	}

	template<typename T>
	Service<T>::Service(Device& device)
	{
		m_pService = device.Activate(__uuidof(T));
	}

	template<typename T>
	T Service<T>::GetService() const
	{
		return m_pService;
	}

} // namespace Media
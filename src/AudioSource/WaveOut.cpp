#include <AudioSource/WaveOut.h>

namespace Media {

	WaveOut::WaveOut(std::string filepath)
	{
		m_File.open("res/w.wav", std::ios::binary);

		if (!m_File) {
			LOG_INFO("Bug!");
		}
		else {
			while (!m_File.eof()) {
				uint32_t data;
				m_File.getline(reinterpret_cast<char*>(&data), sizeof(data));
				LOG_INFO(std::to_string(data));
			}
		}
	}

} // namespace Media
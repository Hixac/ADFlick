#include <AudioSource/WaveOut.h>

namespace Media {

	WaveOut::WaveOut(const std::string& filepath)
	{
		std::vector<uint8_t> bytes;
		ReadFile(bytes, filepath, 4);

		for (size_t i = 0; i < bytes.size(); i++)
		{
			LOG_INFO(std::to_string(bytes[i]));
		}
	}

} // namespace Media
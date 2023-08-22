#pragma once

#include <Base.h>

#include <vector>
#include <fstream>

namespace Media {

	enum class Format { None, WaveFormatPCM };

	struct WavData
	{
		Format format;
		uint32_t filesize;
		uint16_t channels;
		uint32_t samplerate;
		uint32_t byterate;
		uint16_t blockallign;
		uint16_t bitspersample;
	};

	class WaveOut
	{
	public:
		WaveOut(std::string filepath);
		~WaveOut() = default;

	private:
		std::fstream m_File;

		std::vector<uint32_t> m_Data;
	};
	
} // namespace Media
#pragma once

#include <Base.h>
#include <FileRead.h>

#include <vector>

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
		WaveOut(const std::string& filepath);
		~WaveOut() = default;

	private:
		Format GetFileFormat();

		WavData m_WaveHeader;
	};
	
} // namespace Media
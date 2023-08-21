#pragma once

#include <Base.h>

namespace Media {

	enum class Format { None, WaveFormatPCM };

	struct WavData
	{
		Format format;
		uint32_t filesize;

	};

	class WaveOut
	{
	public:

	};
	
} // namespace Media
#pragma once

namespace Media {

	class IVolume // For an exclusive and shared-mode volume changing.
	{
	public:
		virtual ~IVolume() = default;

		virtual size_t GetVolume() const = 0;
		virtual void SetVolume(size_t to) = 0;
	};

} // namespace Media
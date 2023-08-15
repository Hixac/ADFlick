#pragma once

#include <string>

#define SPDLOG_WCHAR_TO_UTF8_SUPPORT 
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Log {

	enum class Types 
	{
		Info, Warn, Critical, Error
	};

	class LoggingSystem
	{
	public:
		static void Instantiate(const std::string name)
		{
			m_IsInited = true;

			auto logger = spdlog::basic_logger_mt(name, "log/" + name + ".txt");
			logger->set_level(spdlog::level::level_enum::debug);
			logger->flush_on(spdlog::level::info);

			m_Name = name; // Because of the complexity type I use spdlog::get instead of logger itself.
		}

		static void Send(const std::string text, const Types type)
		{
			if (!m_IsInited)
			{
				spdlog::error("Logging system haven't initialized!");
				__debugbreak();
			}

			switch (type)
			{
			case Types::Info:
				spdlog::info(text);
				spdlog::get(m_Name)->info(text);
				return;
			case Types::Warn:
				spdlog::warn(text);
				spdlog::get(m_Name)->warn(text);
				return;
			case Types::Critical:
				spdlog::critical(text);
				spdlog::get(m_Name)->critical(text);
				return;
			case Types::Error:
				spdlog::error(text);
				spdlog::get(m_Name)->error(text);
				return;
			}
		}

		static void Send(const std::wstring text, const Types type)
		{
			if (!m_IsInited)
			{
				spdlog::error("Logging system haven't initialized!");
				__debugbreak();
			}

			switch (type)
			{
			case Types::Info:
				spdlog::info(text);
				spdlog::get(m_Name)->info(text);
				return;
			case Types::Warn:
				spdlog::warn(text);
				spdlog::get(m_Name)->warn(text);
				return;
			case Types::Critical:
				spdlog::critical(text);
				spdlog::get(m_Name)->critical(text);
				return;
			case Types::Error:
				spdlog::error(text);
				spdlog::get(m_Name)->error(text);
				return;
			}
		}
	private:
		inline static std::string m_Name;
		inline static bool m_IsInited = false;
	};

}
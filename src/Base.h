#pragma once

#include <LoggingSystem.h>
#include <wrl/client.h>

#ifdef _DEBUG
	#define LOG_WARN(x) Log::LoggingSystem::Send(x, Log::Types::Warn)
	#define LOG_CRITICAL(x) Log::LoggingSystem::Send(x, Log::Types::Critical)
	#define LOG_INFO(x) Log::LoggingSystem::Send(x, Log::Types::Info)
	#define LOG_ERROR(x) Log::LoggingSystem::Send(x, Log::Types::Error)

	#define INIT_LOG() spdlog::set_level(spdlog::level::level_enum::debug);\
					   Log::LoggingSystem::Instantiate("Logger");\
					   LOG_INFO("Log system has initialized!")
#else
	#define LOG_WARN(x)
	#define LOG_CRITICAL(x)
	#define LOG_INFO(x)
	#define LOG_ERROR(x)

	#define INIT_LOG()
#endif

#define ASSERT(x) spdlog::error(x); __debugbreak()

#define CHECK(hr) if (!SUCCEEDED(hr)) __debugbreak()
#define SAFE_RELEASE(x)\
			if ((x) != nullptr)\
			{\
				(x)->Release();\
				(x) = nullptr;\
				LOG_INFO(std::string(#x) + " has been successfully released!");\
			}

template<typename T>
using COMScope = Microsoft::WRL::ComPtr<T>;
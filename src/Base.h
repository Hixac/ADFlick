#pragma once

#include <LoggingSystem.h>
#include <memory>
#include <wrl/client.h>

#ifdef _DEBUG
	#define LOG_WARN(x) Log::LoggingSystem::Send(x, Log::Types::Warn)
	#define LOG_CRITICAL(x) Log::LoggingSystem::Send(x, Log::Types::Critical)
	#define LOG_INFO(x) Log::LoggingSystem::Send(x, Log::Types::Info)
	#define LOG_ERROR(x) Log::LoggingSystem::Send(x, Log::Types::Error)

	#define INIT_LOG() Log::LoggingSystem::Instantiate("Logger");\
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

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}
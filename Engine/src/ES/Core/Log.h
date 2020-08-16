#pragma once
#include "ES/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ES {
	class   Log
	{
	public:
		
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	
	
}
//core log macros
#define ES_CORE_INFO(...)   ::ES::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ES_CORE_TRACE(...)  ::ES::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ES_CORE_WARN(...)   ::ES::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ES_CORE_ERROR(...)  ::ES::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ES_CORE_CRITICAL(...)  ::ES::Log::GetCoreLogger()->critical(__VA_ARGS__)

//client log macros
#define ES_INFO(...)   ::ES::Log::GetClientLogger()->info(__VA_ARGS__)
#define ES_TRACE(...)  ::ES::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ES_WARN(...)   ::ES::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ES_ERROR(...)  ::ES::Log::GetClientLogger()->error(__VA_ARGS__)
#define ES_CRITICAL(...)  ::ES::Log::GetClientLogger()->critical(__VA_ARGS__)

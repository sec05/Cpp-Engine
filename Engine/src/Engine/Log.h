#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <memory.h>
namespace Engine {
	class ES_API Log
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
#define ES_CORE_INFO(...)   ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ES_CORE_TRACE(...)  ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ES_CORE_WARN(...)   ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ES_CORE_ERROR(...)  ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ES_CORE_CRITICAL(...)  ::Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)

//client log macros
#define ES_INFO(...)   ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ES_TRACE(...)  ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ES_WARN(...)   ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ES_ERROR(...)  ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define ES_CRITICAL(...)  ::Engine::Log::GetClientLogger()->critical(__VA_ARGS__)

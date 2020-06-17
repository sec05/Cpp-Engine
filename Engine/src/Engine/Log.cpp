#include "espch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Engine {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");//time stamp name of logger and then the message
		s_CoreLogger = spdlog::stdout_color_mt("ENGINE");//name of the message
		s_CoreLogger->set_level(spdlog::level::trace);//prints all of the message

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}
#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Almond {

	class ALMOND_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger();
		inline static std::shared_ptr<spdlog::logger>& getClientLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		
	};
}


//Core Log Macros
#define AL_CORE_ERROR(...)	::Almond::Log::getCoreLogger()->error(__VA_ARGS__)
#define AL_CORE_WARN(...)	::Almond::Log::getCoreLogger()->warn(__VA_ARGS__)
#define AL_CORE_INFO(...)	::Almond::Log::getCoreLogger()->info(__VA_ARGS__)
#define AL_CORE_TRACE(...)	::Almond::Log::getCoreLogger()->trace(__VA_ARGS__)
#define AL_CORE_FATAL(...)	::Almond::Log::getCoreLogger()->critical(__VA_ARGS__)

//Client logging macros

#define AL_ERROR(...)		::Almond::Log::getClientLogger()->error(__VA_ARGS__)
#define AL_WARN(...)		::Almond::Log::getClientLogger()->warn(__VA_ARGS__)
#define AL_INFO(...)		::Almond::Log::getClientLogger()->info(__VA_ARGS__)
#define AL_TRACE(...)		::Almond::Log::getClientLogger()->trace(__VA_ARGS__)
#define AL_FATAL(...)		::Almond::Log::getClientLogger()->critical(__VA_ARGS__)
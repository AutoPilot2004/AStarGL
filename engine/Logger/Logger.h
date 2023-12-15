#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define ENGINE_NAME      "ENGINE"
#define APPLICATION_NAME "APPLICATION"

#ifdef ENGINE
	#define GET_LOG() spdlog::get(ENGINE_NAME)
#else
	#define GET_LOG() spdlog::get(APPLICATION_NAME)
#endif

#define TRACE_LOG(x, ...)     GET_LOG()->trace(x,##__VA_ARGS__);
#define INFO_LOG(x, ...)      GET_LOG()->info(x,##__VA_ARGS__);
#define WARN_LOG(x, ...)      GET_LOG()->warn(x,##__VA_ARGS__);
#define ERROR_LOG(x, ...)     GET_LOG()->error(x,##__VA_ARGS__);
#define CRITICAL_LOG(x, ...)  GET_LOG()->critical(x,##__VA_ARGS__);

namespace engine
{
	enum class LOG_LEVEL
	{
		OFF =       spdlog::level::level_enum::off,
		TRACE =     spdlog::level::level_enum::trace,
		INFO =      spdlog::level::level_enum::info,
		WARN =      spdlog::level::level_enum::warn,
		ERROR =     spdlog::level::level_enum::err,
		CRITICAL =  spdlog::level::level_enum::critical
	};

	namespace Logger
	{
		extern void init(LOG_LEVEL log_level);
		extern void set_level(LOG_LEVEL log_level);
	}
}
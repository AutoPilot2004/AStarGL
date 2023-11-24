#include "Logger.h"

namespace engine
{
	namespace Logger
	{
		void init(LOG_LEVEL log_level)
		{
			spdlog::set_pattern("[%H:%M:%S %z] [thread %t] [%^%l%$] [%n]: %v");
			set_level(log_level);

			spdlog::stdout_color_mt(ENGINE_NAME);
			spdlog::stderr_color_mt(APPLICATION_NAME);

			INFO_LOG("Logger initialized.")
		}

		void set_level(LOG_LEVEL log_level)
		{
			spdlog::set_level(static_cast<spdlog::level::level_enum>(log_level));
		}
	}
}
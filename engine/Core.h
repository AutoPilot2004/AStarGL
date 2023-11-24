#pragma once
#include <string>
#include <csignal>

#include "Logger/Logger.h"

#define BIT_LEFT_SHIFT(x) 1 << x

#define ASSERT(expression) if (!(expression)) raise(SIGABRT);

#define FATAL_ERROR(x, ...) CRITICAL_LOG(x, __VA_ARGS__) \
							engine::fatalError();

namespace engine
{
	extern void init(LOG_LEVEL log_level = LOG_LEVEL::TRACE);
	extern void destroy();

	[[noreturn]] extern void fatalError();
}
#include "Core.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window/Window.h"

namespace
{
	void initGLFW()
	{
		INFO_LOG("Initializing GLFW.")

		if (!glfwInit()) {
			FATAL_ERROR("Couldn't initialize GLFW!")
		}
	}

	void initGLEW()
	{
		INFO_LOG("Initializing GLEW.")

		if (glewInit() != GLEW_OK) {
			FATAL_ERROR("Couldn't initialize GLEW!")
		}
	}
}

namespace engine
{
	void init(LOG_LEVEL log_level /* = LOG_LEVEL::TRACE */)
	{
		Logger::init(log_level);
		INFO_LOG("Initializing ENGINE.")
		initGLFW();
		Logger::set_level(LOG_LEVEL::OFF);

		{
			WindowSettings tmpSettings("", 1, 1, WindowFlags::INVISIBLE);
			Window tmpWin(tmpSettings);
			tmpWin.create();

			Logger::set_level(log_level);
			initGLEW();
			Logger::set_level(LOG_LEVEL::OFF);
		}

		Logger::set_level(log_level);
	}

	void destroy()
	{
		glfwTerminate();
	}

	[[noreturn]] void fatalError()
	{
		destroy();
		std::cout << "\nPress enter to exit...";
		std::cin.get();
		std::exit(-1);
	}
}
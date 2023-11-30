#include "Application.h"

namespace engine
{
	void Application::run()
	{
		engine::init();
		init();
		mainLoop();
		engine::destroy();
	}
}
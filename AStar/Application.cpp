#include "Application.h"
#include "GameScene.h"
#include <chrono>

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

void Application::init()
{
	engine::WindowSettings windowSettings
	{
		.title = "AStar Algorithm",
		.width = SCREEN_WIDTH,
		.height = SCREEN_HEIGHT
	};

	window.setSettings(windowSettings);
	window.create();
	createApplicationContext();

	bindScene<GameScene>();
}

void Application::mainLoop()
{
	auto startTime = std::chrono::high_resolution_clock::now();

	while (!window.isClosed()) {
		auto duration = (std::chrono::high_resolution_clock::now() - startTime).count() / 1'000'000.0f;
		startTime = std::chrono::high_resolution_clock::now();

		getBoundScene()->onUpdate(duration);
		getBoundScene()->onRender();

		window.update();
	}
}
#include "Application.h"
#include <chrono>

#include "FadeScene.h"
#include "GameScene.h"
#include "MenuScene.h"

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

	addScene<FadeScene>([]() {std::cout << "FADE IN COMPLETE\n"; }, [&]() {std::cout << "FADE OUT COMPLETE\n"; bindScene<MenuScene>(); m_fadeScene->fadeIn(); });
	m_fadeScene = getScene<FadeScene>();
	addScene<MenuScene>();
	addScene<GameScene>([&]() {std::cout << "EXIT\n"; m_fadeScene->fadeOut(); });
	bindScene<GameScene>();
}

void Application::mainLoop()
{
	auto startTime = std::chrono::high_resolution_clock::now();

	while (!window.isClosed()) {
		auto duration = (std::chrono::high_resolution_clock::now() - startTime).count() / 1'000'000.0f;
		startTime = std::chrono::high_resolution_clock::now();

		m_fadeScene->onUpdate(duration);

		getBoundScene()->onUpdate(duration);
		getBoundScene()->onRender();

		m_fadeScene->onRender();

		window.update();
	}
}
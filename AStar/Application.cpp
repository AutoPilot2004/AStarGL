#include "Application.h"
#include <chrono>

#include <engine/Renderer/RenderCommand.h>

#include "FadeScene.h"
#include "GameScene.h"
#include "MenuScene.h"

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

#define BC_RED   0.2f
#define BC_GREEN 0.2f
#define BC_BLUE  0.2f
#define BC_ALPHA 1.0f

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

	engine::RenderCommand::setClearColor(BC_RED, BC_GREEN, BC_BLUE, BC_ALPHA);

	addScene<FadeScene>([&]() { bindSceneWithID(m_nextSceneID); m_fadeScene->fadeIn(); });
	m_fadeScene = getScene<FadeScene>();
	addScene<MenuScene>([&](SceneID nextScene) { m_nextSceneID = nextScene; m_fadeScene->fadeOut(); });
	addScene<GameScene>([&](SceneID nextScene) { m_nextSceneID = nextScene; m_fadeScene->fadeOut(); });
	bindScene<MenuScene>();
}

void Application::bindSceneWithID(SceneID scene)
{
	switch (scene) {
	case SceneID::MENU:
		bindScene<MenuScene>();
		break;
	case SceneID::GAME:
		bindScene<GameScene>();
		break;
	}
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
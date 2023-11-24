#include "Application.h"

#include <engine/Core.h>
#include <engine/Renderer/Renderer2D.h>
#include <engine/Renderer/RenderCommand.h>
#include <engine/Management/Textures/TextureManager.h>

#include <chrono>

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

Application::Application()
	: m_camera2D(m_window.eventManager.dispatcher, 10.0f)
{}

void Application::init()
{
	engine::init();

	m_window.setSettings({ "AStar Algorithm", SCREEN_WIDTH, SCREEN_HEIGHT });
	m_window.create();
}

void Application::run()
{
	init();
	mainLoop();
}

void Application::mainLoop()
{
	engine::RenderCommand::setClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	engine::TextureManager texMan;

	engine::Renderer2D r2D(texMan);

	m_board.init(1, 1, 0.5f);

	auto startTime = std::chrono::high_resolution_clock::now();

	while (!m_window.isClosed()) {
		double dT = (std::chrono::high_resolution_clock::now() - startTime).count() / 1'000'000.0f;
		startTime = std::chrono::high_resolution_clock::now();
		INFO_LOG("dT: {}\n", dT);
		engine::RenderCommand::clear(GL_COLOR_BUFFER_BIT);
		//glViewport(0, 0, 100, 100);

		update(dT);
		render(r2D);

		m_window.update();
	}
}

void Application::processInput(double dT)
{
	//if (m_window.eventManager.input.isKeyDown(KEY_A))
}

void Application::update(double dT)
{
	processInput(dT);
}

void Application::render(engine::Renderer2D& renderer)
{
	renderer.beginScene(&m_camera2D);

	m_board.render(renderer);

	renderer.endScene();
}
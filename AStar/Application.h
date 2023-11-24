#pragma once
#include <engine/Scene/Camera2D.h>
#include <engine/Window/Window.h>

#include "Board.h"

namespace engine
{
	class Renderer2D;
}

class Application
{
public:
	Application();

	void run();

private:
	void init();
	void mainLoop();

	void processInput(double dT);
	void update(double dT);
	void render(engine::Renderer2D& renderer);

private:
	engine::Window m_window;
	engine::Camera2D m_camera2D;

	Board m_board;
};
#pragma once
#include "Dispatcher.h"
#include "Input.h"

typedef struct GLFWwindow GLFWwindow;

namespace engine
{
	class EventManager
	{
	public:
		Dispatcher dispatcher;
		Input      input;

	private:
		void        setupGLFWCallbacks(GLFWwindow* handle);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseBtnCallback(GLFWwindow* window, int button, int action, int mods);
		static void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
		static void mouseScrollCallback(GLFWwindow* window, double offX, double offY);
		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

		void update();

		friend class Window;
	};
}
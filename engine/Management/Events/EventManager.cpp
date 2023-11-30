#include "EventManager.h"

#include "Window/Window.h"
#include "Renderer/RenderCommand.h"

#include <GLFW/glfw3.h>

#define GET_WIN static_cast<engine::Window*>(glfwGetWindowUserPointer(window));

namespace engine
{
	void EventManager::setupGLFWCallbacks(GLFWwindow* handle)
	{
		glfwSetKeyCallback(handle, keyCallback);
		glfwSetMouseButtonCallback(handle, mouseBtnCallback);
		glfwSetCursorPosCallback(handle, mousePosCallback);
		glfwSetScrollCallback(handle, mouseScrollCallback);
		glfwSetWindowSizeCallback(handle, windowSizeCallback);
		glfwSetFramebufferSizeCallback(handle, framebufferSizeCallback);

		input.setupCallbacks(dispatcher);
	}

	void EventManager::update()
	{
		input.update();
		glfwPollEvents();
	}

	void EventManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		engine::Window* win = GET_WIN;

		engine::KeyEvent keyEvent = { Event{}, action == GLFW_PRESS, action == GLFW_RELEASE, key };

		win->eventManager.dispatcher.onNotify(keyEvent);
	}

	void EventManager::mouseBtnCallback(GLFWwindow* window, int button, int action, int mods)
	{
		engine::Window* win = GET_WIN;

		engine::MouseBtnEvent mBtnEvent = { Event{}, action == GLFW_PRESS, action == GLFW_RELEASE, button };

		win->eventManager.dispatcher.onNotify(mBtnEvent);
	}

	void EventManager::mousePosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		engine::Window* win = GET_WIN;

		engine::MouseMotionEvent mMotionEvent = { Event{}, { xpos, ypos } };

		win->eventManager.dispatcher.onNotify(mMotionEvent);
	}

	void EventManager::mouseScrollCallback(GLFWwindow* window, double offX, double offY)
	{
		engine::Window* win = GET_WIN;

		engine::MouseScrollEvent mScrollEvent = { Event{}, { offY } };

		win->eventManager.dispatcher.onNotify(mScrollEvent);
	}

	void EventManager::windowSizeCallback(GLFWwindow* window, int width, int height)
	{
		engine::Window* win = GET_WIN;

		engine::WindowResizeEvent winResizeEvent = { Event{}, { width, height } };

		RenderCommand::setWindowSize(width, height);

		win->eventManager.dispatcher.onNotify(winResizeEvent);
	}

	void EventManager::framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		engine::Window* win = GET_WIN;

		engine::FramebufferResizeEvent fbResizeEvent = { Event{}, { width, height } };

		RenderCommand::setViewPort(0, 0, width, height);

		win->eventManager.dispatcher.onNotify(fbResizeEvent);
	}
}
#include "Window.h"
#include "Core.h"
#include "Renderer/RenderCommand.h"

#include <GLFW/glfw3.h>

namespace engine
{
	Window::Window(const WindowSettings& settings)
	{
		setSettings(settings);
	}

	Window::~Window()
	{
		INFO_LOG("Destroying Window.")
		glfwDestroyWindow(m_handle);
	}

	void Window::setSettings(const WindowSettings& settings)
	{
		m_settings = settings;
	}

	void Window::create()
	{
		setupHints();
		createWindow();
	}

	void Window::update()
	{
		glfwSwapBuffers(m_handle);
		eventManager.update();
	}

	bool Window::isClosed() const
	{
		return glfwWindowShouldClose(m_handle);
	}

	void Window::setupHints() const
	{
		TRACE_LOG("Setting up window hints.")

		glfwDefaultWindowHints();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		using ut = std::underlying_type_t<WindowFlags>;

		if (ut(m_settings.flags) & ut(WindowFlags::NOT_RESIZABLE)) {
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}

		if (ut(m_settings.flags) & ut(WindowFlags::INVISIBLE)) {
			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		}
	}

	void Window::createWindow()
	{
		INFO_LOG("Creating window.")

		m_handle = glfwCreateWindow(m_settings.width, m_settings.height, m_settings.title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(m_handle, this);

		if (!m_handle) {
			FATAL_ERROR("Couldn't create GLFW window!")
		}

		setContext();

		RenderCommand::setViewPort(0, 0, m_settings.width, m_settings.height);
	}

	void Window::setContext()
	{
		glfwMakeContextCurrent(m_handle);

		eventManager.setupGLFWCallbacks(m_handle);
	}
}
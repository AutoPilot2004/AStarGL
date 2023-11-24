#pragma once
#include "WindowSettings.h"
#include "Management/Events/EventManager.h"

typedef struct GLFWwindow GLFWwindow;

namespace engine
{
	class Window
	{
	public:
		Window() = default;
		Window(const WindowSettings& settings);
		~Window();

		void setSettings(const WindowSettings& settings);
		void create();
		void update();

		bool isClosed() const;

		inline const WindowSettings& getSettings() const { return m_settings; }

	public:
		EventManager eventManager;

	private:
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

	private:
		void setupHints() const;
		void createWindow();
		void setContext();

	private:
		GLFWwindow* m_handle = nullptr;
		WindowSettings m_settings;
	};
}
#pragma once
#include <array>

#include "Events.h"
#include "KeyCodes.h"

namespace engine
{
	class Dispatcher;

	class Input
	{
	public:
		Input() = default;
		~Input();

		bool isKeyPressed(uint16_t keyCode)  const;
		bool isKeyReleased(uint16_t keyCode) const;
		bool isKeyDown(uint16_t keyCode)     const;

		bool isMouseButtonPressed(uint8_t mouseBtnCode)  const;
		bool isMouseButtonReleased(uint8_t mouseBtnCode) const;
		bool isMouseButtonDown(uint8_t mouseBtnCode)     const;

		//Getters
		inline const glm::vec2& getMousePos() const { return m_mousePos; }

	private:
		Input(const Input&) = delete;
		Input(Input&&) = delete;
		Input& operator=(const Input&) = delete;
		Input& operator=(Input&&) = delete;

	private:
		void setupCallbacks(Dispatcher& d);
		void keyCallback(const KeyEvent& e);
		void mouseBtnCallback(const MouseBtnEvent& e);
		void mousePosCallback(const MouseMotionEvent& e);

		void update();

	private:
		Dispatcher* m_d = nullptr;
		void* DKEY_ID = nullptr;
		void* DMOUSEBTN_ID = nullptr;
		void* DMOUSEPOS_ID = nullptr;

		glm::vec2 m_mousePos;

		std::array<bool, KEY_LAST>                      m_keyPressed{};
		std::array<bool, KEY_LAST>                     m_keyReleased{};
		std::array<bool, KEY_LAST>                         m_keyDown{};

		std::array<bool, MOUSE_BUTTON_LAST>        m_mouseBtnPressed{};
		std::array<bool, MOUSE_BUTTON_LAST>       m_mouseBtnReleased{};
		std::array<bool, MOUSE_BUTTON_LAST>           m_mouseBtnDown{};

		friend class EventManager;
	};
}
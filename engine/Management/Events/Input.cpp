#include "Input.h"
#include "Dispatcher.h"
#include "Core.h"

#define ASSERT_KEY(x)           ASSERT(x >= 0 && x < KEY_LAST)
#define ASSERT_MOUSE_BUTTON(x)  ASSERT(x >= 0 && x < MOUSE_BUTTON_LAST)

namespace engine
{
	Input::~Input()
	{
		m_d->removeListener<KeyEvent>(DKEY_ID);
		m_d->removeListener<MouseBtnEvent>(DMOUSEBTN_ID);
		m_d->removeListener<MouseMotionEvent>(DMOUSEPOS_ID);
	}

	bool Input::isKeyPressed(uint16_t keyCode)
	{
		ASSERT_KEY(keyCode)
		return m_keyPressed.at(keyCode);
	}

	bool Input::isKeyReleased(uint16_t keyCode)
	{
		ASSERT_KEY(keyCode)
		return m_keyReleased.at(keyCode);
	}

	bool Input::isKeyDown(uint16_t keyCode)
	{
		ASSERT_KEY(keyCode)
		return m_keyDown.at(keyCode);
	}

	bool Input::isMouseButtonPressed(uint8_t mouseBtnCode)
	{
		ASSERT_MOUSE_BUTTON(mouseBtnCode)
		return m_mouseBtnPressed.at(mouseBtnCode);
	}

	bool Input::isMouseButtonReleased(uint8_t mouseBtnCode)
	{
		ASSERT_MOUSE_BUTTON(mouseBtnCode)
		return m_mouseBtnReleased.at(mouseBtnCode);
	}

	bool Input::isMouseButtonDown(uint8_t mouseBtnCode)
	{
		ASSERT_MOUSE_BUTTON(mouseBtnCode)
		return m_mouseBtnDown.at(mouseBtnCode);
	}

	void Input::setupCallbacks(Dispatcher& d)
	{
		m_d = &d;

		DKEY_ID      = d.addListener<KeyEvent>(this, &Input::keyCallback);
		DMOUSEBTN_ID = d.addListener<MouseBtnEvent>(this, &Input::mouseBtnCallback);
		DMOUSEPOS_ID = d.addListener<MouseMotionEvent>(this, &Input::mousePosCallback);
	}

	void Input::keyCallback(const KeyEvent& e)
	{
		m_keyPressed.at(e.key) = e.pressed;
		m_keyReleased.at(e.key) = e.released;

		if (e.pressed)
			m_keyDown.at(e.key) = true;
		else if (e.released)
			m_keyDown.at(e.key) = false;
	}

	void Input::mouseBtnCallback(const MouseBtnEvent& e)
	{
		m_mouseBtnPressed.at(e.button) = e.pressed;
		m_mouseBtnReleased.at(e.button) = e.released;

		if (e.pressed)
			m_mouseBtnDown.at(e.button) = true;
		else if (e.released)
			m_mouseBtnDown.at(e.button) = false;
	}

	void Input::mousePosCallback(const MouseMotionEvent& e)
	{
		m_mousePos = e.position;
	}

	void Input::update()
	{
		memset(&m_keyPressed.at(0), false, m_keyPressed.size());
		memset(&m_keyReleased.at(0), false, m_keyReleased.size());

		memset(&m_mouseBtnPressed.at(0), false, m_mouseBtnPressed.size());
		memset(&m_mouseBtnReleased.at(0), false, m_mouseBtnReleased.size());
	}
}
#pragma once
#include <glm/glm.hpp>

namespace engine
{
	struct Event
	{
	};

	struct ActionEvent : public Event
	{
		bool pressed;
		bool released;
	};

	struct ResizeEvent : public Event
	{
		glm::ivec2 size;
	};

	struct MouseMotionEvent : public Event
	{
		glm::dvec2 position;
	};

	struct MouseScrollEvent : public Event
	{
		double offset;
	};

	struct KeyEvent : public ActionEvent
	{
		int key;
	};

	struct MouseBtnEvent : public ActionEvent
	{
		int button;
	};

	struct WindowResizeEvent : public ResizeEvent
	{

	};

	struct FramebufferResizeEvent : public ResizeEvent
	{

	};
}
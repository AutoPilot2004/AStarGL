#pragma once
#include <string>
#include <stdint.h>

#include "Core.h"

namespace engine
{
	enum class WindowFlags : uint16_t
	{
		NONE =           BIT_LEFT_SHIFT(0),
		NOT_RESIZABLE =  BIT_LEFT_SHIFT(1),
		INVISIBLE =      BIT_LEFT_SHIFT(2)
	};

	inline WindowFlags operator|(WindowFlags lhs, WindowFlags rhs)
	{
		return static_cast<WindowFlags>(static_cast<std::underlying_type_t<WindowFlags>>(lhs) | static_cast<std::underlying_type_t<WindowFlags>>(rhs));
	}

	struct WindowSettings
	{
		std::string title = "Window";
		uint16_t width = 1920;
		uint16_t height = 1080;
		WindowFlags flags = WindowFlags::NONE;
	};
}
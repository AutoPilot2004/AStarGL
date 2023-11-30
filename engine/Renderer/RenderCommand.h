#pragma once

#include <cstdint>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace engine
{
	namespace RenderCommand
	{
		extern void clear(GLbitfield mask);
		extern void setClearColor(float r, float g, float b, float a);
		extern void setViewPort(int x, int y, uint16_t width, uint16_t height);
		//DO NOT USE, TODO: REMOVE FROM HERE SO IT ISN'T PUBLIC TO THE USER
		extern void setWindowSize(uint16_t width, uint16_t height);

		extern const glm::ivec4&  getViewPort();
		extern const glm::ivec2&  getWindowSize();
	}
}
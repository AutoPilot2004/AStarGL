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
		extern void setViewPort(int x, int y, uint32_t width, uint32_t height);
		extern const glm::ivec4& getViewPort();
	}
}
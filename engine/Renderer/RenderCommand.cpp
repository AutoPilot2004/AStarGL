#include "RenderCommand.h"

namespace
{
	glm::ivec4 sp_currentViewPort;
}

namespace engine
{
	namespace RenderCommand
	{
		void clear(GLbitfield mask)
		{
			glClear(mask);
		}

		void setClearColor(float r, float g, float b, float a)
		{
			glClearColor(r, g, b, a);
		}

		void setViewPort(int x, int y, uint32_t width, uint32_t height)
		{
			sp_currentViewPort = { x, y, width, height };

			glViewport(x, y, width, height);
		}

		const glm::ivec4& getViewPort()
		{
			return sp_currentViewPort;
		}
	}
}
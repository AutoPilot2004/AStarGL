#include "RenderCommand.h"

namespace
{
	glm::ivec4 sp_currentViewPort;
	glm::ivec2 sp_windowSize;
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

		void setViewPort(int x, int y, uint16_t width, uint16_t height)
		{
			sp_currentViewPort = { x, y, width, height };

			glViewport(x, y, width, height);
		}

		void setWindowSize(uint16_t width, uint16_t height)
		{
			sp_windowSize = { width, height };
		}

		const glm::ivec4& getViewPort()
		{
			return sp_currentViewPort;
		}

		const glm::ivec2& getWindowSize()
		{
			return sp_windowSize;
		}
	}
}
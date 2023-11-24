#pragma once
#include <engine/Shapes/Shapes.h>

#include <vector>
#include <glm/glm.hpp>

namespace engine
{
	class Renderer2D;
}

class Board
{
public:
	void init(uint32_t width, uint32_t height, float rectScale = 1.0f);

	void render(engine::Renderer2D& renderer);

private:
	uint32_t m_width;
	uint32_t m_height;

	engine::Rect           m_rect;
	std::vector<glm::vec4> m_rectColors;
};
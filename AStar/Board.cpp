#include "Board.h"

#include <engine/Renderer/Renderer2D.h>
#include <engine/Graphics/Shader.h>

void Board::init(uint32_t width, uint32_t height, float rectScale /* = 1.0f*/)
{
	static engine::Shader shader;
	shader.create("../Shaders/QuadShader.vert", "../Shaders/QuadShader.frag");

	m_rect.transform.scale = glm::vec2{ rectScale };
	m_rect.shader = &shader;

	m_rectColors.resize((m_width = width) * (m_height = height));
	for (auto& color : m_rectColors)
		color = glm::vec4{ 1.0f };
}

void Board::render(engine::Renderer2D& renderer)
{
	for (uint32_t y = 0; y < m_height; y++) {
		for (uint32_t x = 0; x < m_width; x++) {
			m_rect.transform.translation = glm::vec3{ x, y, 0.0f };
			m_rect.color = m_rectColors[y * m_width + x];
			renderer.drawRect(m_rect);
		}
	}
}
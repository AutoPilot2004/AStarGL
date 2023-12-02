#pragma once
#include <engine/Shapes/Shapes.h>

#include <vector>
#include <glm/glm.hpp>
#include <unordered_set>

namespace engine
{
	struct SceneContext;

	class Renderer2D;
}

class Board
{
public:
	void init(uint32_t width, uint32_t height, const glm::vec4& color, float rectScale = 1.0f);

	void setStartCell(uint32_t x, uint32_t y, const glm::vec4& color);
	void setEndCell(uint32_t x, uint32_t y, const glm::vec4& color);
	void setBlockCell(uint32_t x, uint32_t y, const glm::vec4& color);
	void unsetCell(uint32_t x, uint32_t y);
	void hoverCell(uint32_t x, uint32_t y, const glm::vec4& color);

	void render(const engine::SceneContext& sceneContext);

	bool isCellEmpty(uint32_t x, uint32_t y);

	inline const glm::vec4& getCellColor(uint32_t x, uint32_t y) const { return m_cellColors.at(y * m_width + x); }

private:
	void setCellColor(uint32_t x, uint32_t y, const glm::vec4& color);
	void fill(uint32_t x, uint32_t y);
	void empty(uint32_t x, uint32_t y);

private:
	uint32_t m_width;
	uint32_t m_height;

	glm::vec4 m_color;

	glm::vec2 m_startCell;
	glm::vec2 m_endCell;

	bool m_startCellExists = false;
	bool m_endCellExists   = false;

	engine::Rect                 m_rect;
	std::vector<glm::vec4>       m_cellColors;
	std::unordered_set<uint32_t> m_filledCellIdx;
};
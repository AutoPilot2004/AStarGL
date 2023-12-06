#include "Board.h"

#include <engine/Renderer/Renderer2D.h>
#include <engine/Graphics/Shader.h>
#include <engine/Defaults.h>
#include <engine/Contexts/Contexts.h>

#define IDX_CALC(x, y) (y) * m_width + (x)

void Board::init(uint32_t width, uint32_t height, const glm::vec4& color, float rectScale /* = 1.0f*/)
{
	m_color = color;

	m_rect.transform.scale = glm::vec2{ rectScale };
	m_rect.shader = engine::Defaults::getQuadShader();

	m_cellColors.resize((m_width = width) * (m_height = height));
	m_filledCellIdx.clear();
	m_startCellExists = false;
	m_endCellExists = false;

	for (auto& ccolor : m_cellColors)
		ccolor = color;

	m_astar.reset(width, height);
}

void Board::setCellColor(uint32_t x, uint32_t y, const glm::vec4& color)
{
	m_cellColors.at(IDX_CALC(x, y)) = color;
}

void Board::fill(uint32_t x, uint32_t y)
{
	m_filledCellIdx.emplace(IDX_CALC(x, y));
}

void Board::empty(uint32_t x, uint32_t y)
{
	if (!isCellEmpty(x, y))
		m_filledCellIdx.erase(IDX_CALC(x, y));
}

void Board::setStartCell(uint32_t x, uint32_t y, const glm::vec4& color)
{
	if (!isCellEmpty(x, y)) return;

	if (m_startCellExists) {
		unsetCell(m_startCell.x, m_startCell.y);
	}

	setCellColor(x, y, color);
	fill(x, y);

	m_startCell = { x, y };

	m_startCellExists = true;
}

void Board::setEndCell(uint32_t x, uint32_t y, const glm::vec4& color)
{
	if (!isCellEmpty(x, y)) return;

	if (m_endCellExists) {
		unsetCell(m_endCell.x, m_endCell.y);
	}

	setCellColor(x, y, color);
	fill(x, y);

	m_endCell = { x, y };

	m_endCellExists = true;
}

void Board::setBlockCell(uint32_t x, uint32_t y, const glm::vec4& color)
{
	if (!isCellEmpty(x, y)) return;

	setCellColor(x, y, color);
	fill(x, y);

	m_astar.block(IDX_CALC(x, y));
}

void Board::unsetCell(uint32_t x, uint32_t y)
{
	setCellColor(x, y, m_color);
	empty(x, y);

	m_astar.unblock(IDX_CALC(x, y));

	     if (x == m_startCell.x && y == m_startCell.y) m_startCellExists = false;
	else if (x == m_endCell.x   && y == m_endCell.y)   m_endCellExists   = false;
}

void Board::hoverCell(uint32_t x, uint32_t y, const glm::vec4& color)
{
	setCellColor(x, y, color);
}

bool Board::isCellEmpty(uint32_t x, uint32_t y)
{
	return m_filledCellIdx.find(IDX_CALC(x, y)) == m_filledCellIdx.end();
}

bool Board::computePath(const glm::vec4& color)
{
	if (!m_startCellExists || !m_endCellExists) {
		std::cout << "MISSING START AND/OR END CELL\n\n";
		return false;
	}

	auto pathIndices = m_astar.findPath(IDX_CALC(m_startCell.x, m_startCell.y), IDX_CALC(m_endCell.x, m_endCell.y));

	if (pathIndices.has_value()) {
		const auto& vector = pathIndices.value();

		for (auto idx : vector)
			setBlockCell(idx % m_width, idx / m_width, color);

		return true;
	}

	std::cout << "NO VALID PATH FOUND\n\n";

	m_astar.reset(m_width, m_height);

	for (auto filled : m_filledCellIdx) {
		m_astar.block(filled);
	}

	m_astar.unblock(IDX_CALC(m_startCell.x, m_startCell.y));
	m_astar.unblock(IDX_CALC(m_endCell.x, m_endCell.y));

	return false;
}

void Board::render(const engine::SceneContext& sceneContext)
{
	for (uint32_t y = 0; y < m_height; y++) {
		for (uint32_t x = 0; x < m_width; x++) {
			m_rect.transform.translation = glm::vec3{ x, y, 0.0f };
			m_rect.color = m_cellColors.at(IDX_CALC(x, y));
			sceneContext.renderer2D->drawRect(m_rect);
		}
	}
}
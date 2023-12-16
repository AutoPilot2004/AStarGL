#include "AStarAlgo.h"

#include <cmath>

using Node = impl::Node;

void AStarAlgo::reset(uint32_t width, uint32_t height)
{
	m_nodes.clear();
	m_nodes.resize((m_width = width) * (m_height = height));

	while (!m_openSet.empty())
		m_openSet.pop();

	m_openSetSet.clear();
	m_cameFrom.clear();
}

void AStarAlgo::block(uint32_t index)
{
	m_nodes.at(index).traversable = false;
}

void AStarAlgo::unblock(uint32_t index)
{
	m_nodes.at(index).traversable = true;
}

[[nodiscard]] std::optional<std::vector<uint32_t>> AStarAlgo::findPath(uint32_t start, uint32_t end)
{
	//Manhattan distance
	auto heur = [=](uint32_t nodeIdx) -> uint32_t
		{
			uint32_t nodeX = nodeIdx % m_width;
			uint32_t nodeY = nodeIdx / m_width;

			uint32_t endX = end % m_width;
			uint32_t endY = end / m_width;

			return fabs(nodeX - endX) + fabs(nodeY - endY);
		};

	m_openSet.push({ start, m_nodes.at(start) });

	m_nodes.at(start).gScore = 0;
	m_nodes.at(start).fScore = heur(start);

	m_openSetSet.emplace(start);

	while (!m_openSet.empty()) {
		Node currentNode = m_openSet.top();

		if (currentNode.index == end) {
			std::vector<uint32_t> resultVec;

			uint32_t current = currentNode.index;

			getResult(resultVec, current);

			return resultVec;
		}

		m_openSet.pop();
		m_openSetSet.erase(currentNode.index);

		uint32_t currentX = currentNode.index % m_width;
		uint32_t currentY = currentNode.index / m_width;

		for (int8_t x = -1; x < 2; x += 2) {
			uint32_t neighborX = currentX + x;
			uint32_t neighborNodeIdx = currentY * m_width + neighborX;

			if (neighborX < 0 || neighborX >= m_width || !m_nodes.at(neighborNodeIdx).traversable)
				continue;

			processNeighbor(currentNode, neighborNodeIdx, heur);
		}

		for (int8_t y = -1; y < 2; y += 2) {
			uint32_t neighborY = currentY + y;
			uint32_t neighborNodeIdx = neighborY * m_width + currentX;

			if (neighborY < 0 || neighborY >= m_height || !m_nodes.at(neighborNodeIdx).traversable)
				continue;

			processNeighbor(currentNode, neighborNodeIdx, heur);
		}
	}

	return std::nullopt;
}

void AStarAlgo::processNeighbor(const Node& currentNode, uint32_t neighborNodeIdx, std::function<uint32_t(uint32_t)> heur)
{
	uint32_t tentGScore = m_nodes.at(currentNode.index).gScore + 1;

	if (tentGScore < m_nodes.at(neighborNodeIdx).gScore) {
		m_cameFrom[neighborNodeIdx] = currentNode.index;
		m_nodes.at(neighborNodeIdx).gScore = tentGScore;
		m_nodes.at(neighborNodeIdx).fScore = tentGScore + heur(neighborNodeIdx);
		if (m_openSetSet.find(neighborNodeIdx) == m_openSetSet.end()) {
			m_openSet.push({ neighborNodeIdx, m_nodes.at(neighborNodeIdx) });
			m_openSetSet.emplace(neighborNodeIdx);
		}
	}
}

void AStarAlgo::getResult(std::vector<uint32_t>& res, uint32_t current)
{
	if (m_cameFrom.find(current) == m_cameFrom.end()) {
		res.push_back(current);
		return;
	}

	getResult(res, m_cameFrom.at(current));

	res.push_back(current);
}
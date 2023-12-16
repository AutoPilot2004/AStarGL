#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <optional>
#include <functional>
#include <cstdint>

namespace impl
{
	struct PathNode
	{
		bool traversable = true;
		uint32_t  gScore = std::numeric_limits<uint32_t>::max();
		uint32_t  fScore = std::numeric_limits<uint32_t>::max();
	};

	struct Node
	{
		uint32_t index;
		PathNode node;

		bool operator>(const Node& rhs) const
		{
			return node.fScore > rhs.node.fScore;
		}
	};
}

class AStarAlgo
{
public:
	void reset(uint32_t width, uint32_t height);

	void block(uint32_t index);
	void unblock(uint32_t index);

	[[nodiscard]] std::optional<std::vector<uint32_t>> findPath(uint32_t start, uint32_t end);

	inline const std::unordered_set<uint32_t>& getOpenSet() const { return m_openSetSet; }

private:
	void processNeighbor(const impl::Node& currentNode, uint32_t neighborNodeIdx, std::function<uint32_t(uint32_t)> heur);
	void getResult(std::vector<uint32_t>& res, uint32_t current);

private:
	uint32_t m_width;
	uint32_t m_height;

	std::vector<impl::PathNode>                                                          m_nodes;
	std::priority_queue<impl::Node, std::vector<impl::Node>, std::greater<impl::Node>> m_openSet;
	std::unordered_set<uint32_t>                                                    m_openSetSet;
	std::unordered_map<uint32_t, uint32_t>                                            m_cameFrom;
};
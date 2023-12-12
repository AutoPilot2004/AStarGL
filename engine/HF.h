#pragma once
#include <glm/glm.hpp>

namespace engine
{
	namespace HF
	{
		[[nodiscard]] extern glm::vec2 screenToWorldSpace(const glm::vec2& screenPos, const glm::ivec2& screenWidthHeight, const glm::mat4& viewProjectionMatrix);
	}
}
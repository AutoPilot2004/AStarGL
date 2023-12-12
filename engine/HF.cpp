#include "HF.h"

namespace engine
{
	namespace HF
	{
		[[nodiscard]] glm::vec2 screenToWorldSpace(const glm::vec2& screenPos, const glm::ivec2& screenWidthHeight, const glm::mat4& viewProjectionMatrix)
		{
			glm::vec2 finalPos;

			const int& width = screenWidthHeight.x;
			const int& height = screenWidthHeight.y;

			finalPos.x = (screenPos.x / width) * 2.0f - 1.0f;
			finalPos.y = ((height - screenPos.y) / height) * 2.0f - 1.0f;

			glm::vec4 temp = glm::inverse(viewProjectionMatrix) * glm::vec4(finalPos, 1.0f, 1.0f);

			finalPos = { temp.x, temp.y };

			return finalPos;
		}
	}
}
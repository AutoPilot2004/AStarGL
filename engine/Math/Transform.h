#pragma once
#include <glm/glm.hpp>

namespace engine
{
	class Transform
	{
	public:
		bool needsUpdate() const { return m_translationDirty || m_rotationDirty || m_scaleDirty; }

		//Getters
		inline const glm::mat4& getTransformMatrix() { if (needsUpdate()) updateTransformMatrix(); return m_transformMatrix; }

	protected:
		Transform() = default;

	protected:
		virtual void updateTransformMatrix() = 0;

	protected:
		glm::mat4 m_transformMatrix{ 1.0f };

		glm::mat4 m_translationMatrix{ 1.0f };
		glm::mat4 m_rotationMatrix{ 1.0f };
		glm::mat4 m_scaleMatrix{ 1.0f };

		bool m_translationDirty = true;
		bool m_rotationDirty    = true;
		bool m_scaleDirty       = true;
	};
}
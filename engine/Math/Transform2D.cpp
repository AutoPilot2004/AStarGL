#include "Transform2D.h"

#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
	void Transform2DAdvanced::updateTransformMatrix()
	{
		if (m_translationDirty) {
			m_translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(translation));
			m_translationDirty = false;
		}

		if (m_rotationDirty) {
			m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			m_rotationDirty = false;
		}

		if (m_scaleDirty) {
			m_scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
			m_scaleDirty = false;
		}

		m_transformMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
	}
}
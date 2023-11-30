#include "Projection.h"

#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
	Projection::Projection(uint16_t width, uint16_t height, ProjectionType projectionType)
		: m_width(width), m_height(height), m_projectionType(projectionType)
	{}

	void Projection::updateProjectionMatrix()
	{
		float ar = static_cast<float>(m_width) / static_cast<float>(m_height);

		switch (m_projectionType) {
		case ProjectionType::ORTHOGRAPHIC:
			m_projectionMatrix = glm::ortho(-ar*m_fov, ar*m_fov, -1*m_fov, 1*m_fov);
			break;
		case ProjectionType::PERSPECTIVE:
			//TODO: NEAR/FAR REMOVE HARD CODED VALUES
			m_projectionMatrix = glm::perspective(m_fov, ar, 0.1f, 100.0f);
			break;
		}

		m_dirty = false;
	}
}
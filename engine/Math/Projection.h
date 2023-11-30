#pragma once
#include <glm/glm.hpp>

namespace engine
{
	enum class ProjectionType
	{
		ORTHOGRAPHIC,
		PERSPECTIVE
	};

	class Projection
	{
	public:
		Projection(uint16_t width, uint16_t height, ProjectionType projectionType);

		bool needsUpdate() const { return m_dirty; }

		//Setters
		inline void setWidth(uint16_t width)                { m_width = width;          m_dirty = true; }
		inline void setHeight(uint16_t height)              { m_height = height;        m_dirty = true; }
		inline void setFOV(float fov)                       { m_fov = fov;              m_dirty = true; }
		inline void offsetFOV(float fov)                    { m_fov += fov;             m_dirty = true; }
		inline void setProjectionType(ProjectionType pType) { m_projectionType = pType; m_dirty = true; }

		//Getters
		inline const glm::mat4& getProjectionMatrix() { if (needsUpdate()) updateProjectionMatrix(); return m_projectionMatrix; }
		inline float getFOV() const { return m_fov; }

	private:
		void updateProjectionMatrix();

	private:
		glm::mat4 m_projectionMatrix{ 1.0f };

		uint16_t m_width;
		uint16_t m_height;
		float m_fov = 45.0f;
		ProjectionType m_projectionType = ProjectionType::ORTHOGRAPHIC;

		bool m_dirty = true;
	};
}
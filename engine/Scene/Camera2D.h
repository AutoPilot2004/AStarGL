#pragma once
#include "Math/Projection.h"
#include "Math/Transform2D.h"

namespace engine
{
	class Dispatcher;
	struct FramebufferResizeEvent;

	class Camera2D
	{
	public:
		Camera2D(Dispatcher& dispatcher, ProjectionType projectionType = ProjectionType::ORTHOGRAPHIC);
		~Camera2D();

		void bind();
		void unbind();

		//TODO: CACHE VIEW PROJ MATRIX
		inline glm::mat4 getViewProjectionMatrix() { return projection.getProjectionMatrix() * glm::inverse(transform.getTransformMatrix()); }

	public:
		Transform2DAdvanced transform;
		Projection          projection;

	private:
		Camera2D(const Camera2D&) = delete;
		Camera2D(Camera2D&&) = delete;
		Camera2D& operator=(const Camera2D&) = delete;
		Camera2D& operator=(Camera2D&&) = delete;

	private:
		void framebufferResizeCallback(const FramebufferResizeEvent& e);

	private:
		Dispatcher& m_dispatcher;
		void* DFBRESIZE_ID = nullptr;

		glm::mat4 m_viewProjectionMatrix{ 1.0f };
	};
}
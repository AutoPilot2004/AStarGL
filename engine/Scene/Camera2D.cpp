#include "Camera2D.h"
#include "Management/Events/Dispatcher.h"
#include "Renderer/RenderCommand.h"

#include <GL/glew.h>

namespace engine
{
	Camera2D::Camera2D(Dispatcher& dispatcher, ProjectionType projectionType /* = ProjectionType::ORTHOGRAPHIC */)
		: projection(RenderCommand::getViewPort().z, RenderCommand::getViewPort().w, projectionType), m_dispatcher(dispatcher)
	{}

	Camera2D::~Camera2D()
	{
		unbind();
	}

	void Camera2D::bind()
	{
		if (DFBRESIZE_ID) return;

		DFBRESIZE_ID = m_dispatcher.addListener<FramebufferResizeEvent>(this, &Camera2D::framebufferResizeCallback);
	}

	void Camera2D::unbind()
	{
		if (!DFBRESIZE_ID) return;

		m_dispatcher.removeListener<FramebufferResizeEvent>(DFBRESIZE_ID);
		DFBRESIZE_ID = nullptr;
	}

	void Camera2D::framebufferResizeCallback(const FramebufferResizeEvent& e)
	{
		projection.setWidth(RenderCommand::getViewPort().z);
		projection.setHeight(RenderCommand::getViewPort().w);
	}
}
#include "Camera2D.h"
#include "Management/Events/Dispatcher.h"
#include "Renderer/RenderCommand.h"

#include <GL/glew.h>

namespace engine
{
	Camera2D::Camera2D(Dispatcher& dispatcher, float fov, ProjectionType projectionType /* = ProjectionType::ORTHOGRAPHIC */)
		: projection(RenderCommand::getViewPort().z, RenderCommand::getViewPort().w, fov, projectionType), m_dispatcher(&dispatcher)
	{
		DFBRESIZE_ID = dispatcher.addListener<FramebufferResizeEvent>(this, &Camera2D::framebufferResizeCallback);
	}

	Camera2D::~Camera2D()
	{
		m_dispatcher->removeListener<FramebufferResizeEvent>(DFBRESIZE_ID);
	}

	void Camera2D::framebufferResizeCallback(const FramebufferResizeEvent& e)
	{
		projection.setWidth(RenderCommand::getViewPort().z);
		projection.setHeight(RenderCommand::getViewPort().w);
	}
}
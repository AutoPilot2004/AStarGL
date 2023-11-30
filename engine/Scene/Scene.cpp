#include "Scene.h"

namespace engine
{
	Scene::Scene(const SceneContext& sceneContext)
		: sceneContext(sceneContext), m_cameraManager(*sceneContext.dispatcher)
	{}

	void Scene::addCamera(const std::string& name)
	{
		m_cameraManager.addCamera(name);
	}

	void Scene::removeCamera(const std::string& name)
	{
		m_cameraManager.removeCamera(name);
	}

	void Scene::setCamera(const std::string& name)
	{
		if (m_boundCamera)
			m_boundCamera->unbind();

		m_boundCamera = &getCamera(name);

		m_boundCamera->bind();
	}

	Camera2D& Scene::getCamera(const std::string& name)
	{
		return m_cameraManager.getCamera(name);
	}
}
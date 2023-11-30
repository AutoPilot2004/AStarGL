#include "CameraManager.h"

#include "Management/Events/Dispatcher.h"

namespace engine
{
	CameraManager::CameraManager(Dispatcher& dispatcher)
		: m_dispatcher(dispatcher)
	{}

	void CameraManager::addCamera(const std::string& name)
	{
		if (m_cameras.find(name) != m_cameras.end()) return;

		m_cameras.emplace(std::piecewise_construct, std::make_tuple(name), std::forward_as_tuple(m_dispatcher));
	}

	void CameraManager::removeCamera(const std::string& name)
	{
		if (m_cameras.find(name) == m_cameras.end()) return;

		m_cameras.erase(name);
	}
}
#pragma once
#include <unordered_map>
#include <string>

#include "Core.h"
#include "Scene/Camera2D.h"

namespace engine
{
	class Dispatcher;

	class CameraManager
	{
	public:
		CameraManager(Dispatcher& dispatcher);

		void addCamera(const std::string& name);
		void removeCamera(const std::string& name);

		//Getters
		inline Camera2D& getCamera(const std::string& name) { return m_cameras.at(name); }

	private:
		Dispatcher& m_dispatcher;

		std::unordered_map<std::string, Camera2D> m_cameras;
	};
}
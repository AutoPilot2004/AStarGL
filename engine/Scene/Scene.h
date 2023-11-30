#pragma once

#include <vector>

#include "Camera2D.h"
#include "Contexts/Contexts.h"

namespace engine
{
	class Scene
	{
	public:
		Scene(const SceneContext& sceneContext);

		virtual void onEntry()           = 0;
		virtual void onExit()            = 0;

		virtual void onUpdate(double dT) = 0;
		virtual void onRender()          = 0;

	protected:
		void addCamera(const std::string& name);
		void removeCamera(const std::string& name);
		void setCamera(const std::string& name);

		Camera2D& getCamera(const std::string& name);
		Camera2D& getBoundCamera() { return *m_boundCamera; }

	protected:
		SceneContext sceneContext;

	private:
		CameraManager m_cameraManager;
		Camera2D*     m_boundCamera = nullptr;
	};
}
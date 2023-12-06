#pragma once
#include <vector>
#include <concepts>
#include <utility>

#include "Window/Window.h"
#include "Scene/Scene.h"
#include "Contexts/Contexts.h"

//#include "../AStar/GameScene.h"

//TODO: LOGGING AND ASSERTION EVERYWHERE

namespace engine
{
	class Application
	{
	public:
		void run();

	protected:
		virtual void init() = 0;
		virtual void mainLoop() = 0;

		void createApplicationContext()
		{
			m_applicationContext = std::make_unique<ApplicationContext>();
		}

		template<typename SceneName, typename... Args>
		requires std::derived_from<SceneName, Scene>
		void addScene(Args&&... args)
		{
			//TODO: A PROPER SCENE MANAGER

			static bool added = false;

			if (!added) {
				getScene<SceneName>();
				m_scenes.emplace_back(std::make_unique<SceneName>(SceneContext{ .dispatcher = &window.eventManager.dispatcher, .input = &window.eventManager.input, .textureManager = &m_applicationContext->textureManager, .renderer2D = &m_applicationContext->renderer2D }, std::forward<Args>(args)...));
				added = true;
			}
		}

		template<typename SceneName>
		requires std::derived_from<SceneName, Scene>
		[[nodiscard]] SceneName* getScene() const
		{
			static size_t idx = m_scenes.size();

			static bool first = true;

			if (first) {
				first = false;
				return nullptr;
			}

			return static_cast<SceneName*>(m_scenes.at(idx).get());
		}

		template<typename SceneName>
		requires std::derived_from<SceneName, Scene>
		void bindScene()
		{	
			if (m_currentScene)
				m_currentScene->onExit();

			m_currentScene = getScene<SceneName>();

			m_currentScene->onEntry();
		}

		inline Scene* getBoundScene() const { return m_currentScene; }

	protected:
		Window window;
		
	private:
		std::unique_ptr<ApplicationContext> m_applicationContext;

		std::vector<std::unique_ptr<Scene>> m_scenes;
		Scene*                              m_currentScene = nullptr;
	};
}
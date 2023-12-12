#pragma once
#include <engine/Scene/Scene.h>
#include <engine/Shapes/Shapes.h>

#include "SceneID.h"

class MenuScene : public engine::Scene
{
public:
	MenuScene(const engine::SceneContext& sceneContext, const std::function<void(SceneID nextScene)>& exitCallback);

	void onEntry()           override;
	void onExit()            override;

	void onUpdate(double dT) override;
	void onRender()          override;

private:
	engine::Rect m_button;

	std::function<void(SceneID nextScene)> m_exitCallback;
};
#pragma once
#include <engine/Scene/Scene.h>
#include <engine/Shapes/Shapes.h>

class MenuScene : public engine::Scene
{
public:
	MenuScene(const engine::SceneContext& sceneContext);

	void onEntry()           override;
	void onExit()            override;

	void onUpdate(double dT) override;
	void onRender()          override;

private:
	engine::Rect m_rect;
};
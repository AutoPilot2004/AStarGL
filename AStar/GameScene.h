#pragma once
#include <engine/Scene/Scene.h>
#include <engine/Shapes/Shapes.h>

#include "Board.h"

class GameScene : public engine::Scene
{
public:
	GameScene(const engine::SceneContext& sceneContext);

	void onEntry()           override;
	void onExit()            override;

	void onUpdate(double dT) override;
	void onRender()          override;

private:
	Board m_board;
};
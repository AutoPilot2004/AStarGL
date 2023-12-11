#pragma once
#include <engine/Scene/Scene.h>
#include <engine/Shapes/Shapes.h>

#include "Board.h"

class GameScene : public engine::Scene
{
public:
	GameScene(const engine::SceneContext& sceneContext, const std::function<void()>& exitCallback);

	void onEntry()           override;
	void onExit()            override;

	void onUpdate(double dT) override;
	void onRender()          override;

private:
	void initBoard();

	void updateCamera(double dT);
	void updateCameraTranslation(float xy, float bound, bool inv, double distance, bool xAxis);
	void updateChoice();
	void updateBoard();
	void changeState();

private:
	Board m_board;
	bool m_disableMouseInput = false;

	glm::vec4 m_currentColor;

	std::function<void()> m_exitCallback;
};
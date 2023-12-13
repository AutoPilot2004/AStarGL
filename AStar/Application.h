#pragma once
#include <engine/Application.h>
#include "SceneID.h"

class FadeScene;

class Application : public engine::Application
{
public:
	void init() override;
	void mainLoop() override;

private:
	void bindSceneWithID(SceneID scene);

private:
	SceneID m_nextSceneID;

	FadeScene* m_fadeScene = nullptr;
};
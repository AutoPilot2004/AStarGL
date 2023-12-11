#pragma once
#include <engine/Application.h>

class FadeScene;

enum class ApplicationState
{
	ACTIVE,
	IN_TRANSITION
};

class Application : public engine::Application
{
public:
	void init() override;
	void mainLoop() override;

private:
	ApplicationState m_appState = ApplicationState::ACTIVE;

	FadeScene* m_fadeScene = nullptr;
};
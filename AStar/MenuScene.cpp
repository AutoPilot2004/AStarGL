#include "MenuScene.h"

#include <engine/Defaults.h>
#include <engine/Renderer/RenderCommand.h>

#define BC_RED   0.2f
#define BC_GREEN 0.8f
#define BC_BLUE  0.5f
#define BC_ALPHA 1.0f

MenuScene::MenuScene(const engine::SceneContext& sceneContext)
	: engine::Scene(sceneContext)
{
	m_rect.shader = engine::Defaults::getQuadShader();
}

void MenuScene::onEntry()
{
	engine::RenderCommand::setClearColor(BC_RED, BC_GREEN, BC_BLUE, BC_ALPHA);
}

void MenuScene::onExit()
{

}

void MenuScene::onUpdate(double dT)
{

}

void MenuScene::onRender()
{
	engine::RenderCommand::clear(GL_COLOR_BUFFER_BIT);
}
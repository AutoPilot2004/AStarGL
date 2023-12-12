#include "MenuScene.h"

#include <engine/Defaults.h>
#include <engine/HF.h>
#include <engine/Renderer/RenderCommand.h>

#define BUTTON_COLOR       glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}
#define BUTTON_HOVER_COLOR glm::vec4{0.0f, 0.5f, 0.0f, 1.0f}

MenuScene::MenuScene(const engine::SceneContext& sceneContext, const std::function<void(SceneID nextScene)>& exitCallback)
	: engine::Scene(sceneContext), m_exitCallback(exitCallback)
{
	addCamera("Menu");
	setCamera("Menu");

	m_button.shader = engine::Defaults::getQuadShader();
	m_button.transform.scale = { 10.0f, 5.0f };
	m_button.rounding = 1.0f;
}

void MenuScene::onEntry()
{

}

void MenuScene::onExit()
{

}

void MenuScene::onUpdate(double dT)
{
	glm::vec2 wmp = engine::HF::screenToWorldSpace(sceneContext.input->getMousePos(), engine::RenderCommand::getWindowSize(), getBoundCamera().getViewProjectionMatrix());

	const glm::vec2& sc = m_button.transform.scale;

	if (!(wmp.x <= sc.x / 2.0f && wmp.x >= -sc.x / 2.0f && wmp.y <= sc.y / 2.0f && wmp.y >= -sc.y / 2.0f)) { m_button.color = BUTTON_COLOR; return; }

	if (sceneContext.input->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		m_button.color = BUTTON_HOVER_COLOR + glm::vec4{glm::vec3{0.2f}, 0.0f};
		m_exitCallback(SceneID::GAME);
		return;
	}

	m_button.color = BUTTON_HOVER_COLOR;
}

void MenuScene::onRender()
{
	engine::RenderCommand::clear(GL_COLOR_BUFFER_BIT);
	
	sceneContext.renderer2D->beginScene(&getBoundCamera());

	sceneContext.renderer2D->drawRect(m_button);

	sceneContext.renderer2D->endScene();
}
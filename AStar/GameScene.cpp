#include "GameScene.h"

#include <engine/Renderer/RenderCommand.h>
#include <engine/Defaults.h>

namespace
{
	glm::vec2 screenToWorldSpace(const glm::vec2& pos, const glm::ivec2& maxWidth_maxHeight, const glm::mat4& viewProjectionMatrix)
	{
		glm::vec2 finalPos;

		const int& width = maxWidth_maxHeight.x;
		const int& height = maxWidth_maxHeight.y;

		finalPos.x = (pos.x / width)  * 2.0f - 1.0f;
		finalPos.y = ((height - pos.y) / height) * 2.0f - 1.0f;

		glm::vec4 temp = viewProjectionMatrix * glm::vec4(finalPos, 1.0f, 1.0f);

		finalPos = { temp.x, temp.y };

		return finalPos;
	}
}

GameScene::GameScene(const engine::SceneContext& sceneContext)
	: engine::Scene(sceneContext)
{
	addCamera("MainCamera");
	setCamera("MainCamera");
	getBoundCamera().projection.setFOV(1.0f);
	getBoundCamera().transform.setTranslation({ 0.f, 0.f, 0 });
	m_board.init(1, 1);
}

void GameScene::onEntry()
{
	engine::RenderCommand::setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void GameScene::onExit()
{

}

void GameScene::onUpdate(double dT)
{
	if (sceneContext.input->isKeyDown(KEY_D)) getBoundCamera().transform.offsetTranslation({ 0.3f, 0.0f, 0.0f });
	if (sceneContext.input->isKeyDown(KEY_A)) getBoundCamera().transform.offsetTranslation({ -0.3f, 0.0f, 0.0f });
	if (sceneContext.input->isKeyDown(KEY_S)) getBoundCamera().transform.offsetTranslation({ 0.0f, -0.3f, 0.0f });
	if (sceneContext.input->isKeyDown(KEY_W)) getBoundCamera().transform.offsetTranslation({ 0.0f, 0.3f, 0.0f });
	if (sceneContext.input->isKeyDown(KEY_Q)) getBoundCamera().projection.offsetFOV(0.003f);
	if (sceneContext.input->isKeyDown(KEY_E)) getBoundCamera().projection.offsetFOV(-0.003f);
	const glm::vec2& mousePos = sceneContext.input->getMousePos();
	glm::vec2 ws = screenToWorldSpace(mousePos, engine::RenderCommand::getWindowSize(), glm::inverse(getBoundCamera().getViewProjectionMatrix()));
	INFO_LOG("{} {}\n", ws.x, ws.y)
}

void GameScene::onRender()
{
	engine::RenderCommand::clear(GL_COLOR_BUFFER_BIT);

	sceneContext.renderer2D->beginScene(&getBoundCamera());

	m_board.render(sceneContext);

	sceneContext.renderer2D->endScene();
}
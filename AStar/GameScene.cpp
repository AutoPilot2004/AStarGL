#include "GameScene.h"

#include <engine/Renderer/RenderCommand.h>
#include <engine/Defaults.h>

#define BOARD_WIDTH  25
#define BOARD_HEIGHT 50

#define MOVE_SPEED   0.05f
#define SCROLL_SPEED 0.05f

#define MAX_ZOOM_IN  5.0f
#define MAX_ZOOM_OUT 40.0f

#define BC_RED   0.2f
#define BC_GREEN 0.2f
#define BC_BLUE  0.2f
#define BC_ALPHA 1.0f

#define BOARD_COLOR glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}
#define START_COLOR glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}
#define END_COLOR   glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}
#define BLOCK_COLOR glm::vec4{0.5f, 0.5f, 0.5f, 1.0f}
#define PATH_COLOR  glm::vec4{0.3f, 0.5f, 0.6f, 1.0f}

namespace
{
	glm::vec2 screenToWorldSpace(const glm::vec2& pos, const glm::ivec2& screenWidthHeight, const glm::mat4& viewProjectionMatrix)
	{
		glm::vec2 finalPos;

		const int& width = screenWidthHeight.x;
		const int& height = screenWidthHeight.y;

		finalPos.x = (pos.x / width)  * 2.0f - 1.0f;
		finalPos.y = ((height - pos.y) / height) * 2.0f - 1.0f;

		glm::vec4 temp = glm::inverse(viewProjectionMatrix) * glm::vec4(finalPos, 1.0f, 1.0f);

		finalPos = { temp.x, temp.y };

		return finalPos;
	}
}

GameScene::GameScene(const engine::SceneContext& sceneContext)
	: engine::Scene(sceneContext)
{
	addCamera("MainCamera");
}

void GameScene::onEntry()
{
	engine::RenderCommand::setClearColor(BC_RED, BC_GREEN, BC_BLUE, BC_ALPHA);

	setCamera("MainCamera");
	getBoundCamera().projection.setFOV(10.0f);
	getBoundCamera().transform.setTranslation({ (BOARD_WIDTH - 1) / 2.0f, (BOARD_HEIGHT - 1) / 2.0f, 0.0f });

	initBoard();

	m_currentColor = BLOCK_COLOR;
}

void GameScene::initBoard()
{
	m_board.init(BOARD_WIDTH, BOARD_HEIGHT, BOARD_COLOR);
}

void GameScene::onExit()
{

}

void GameScene::updateCamera(double dT)
{
	const double moveSpeed   = MOVE_SPEED   * dT;
	const double scrollSpeed = SCROLL_SPEED * dT;

	engine::Transform2DAdvanced& cTransform = getBoundCamera().transform;

	     if (sceneContext.input->isKeyDown(KEY_A)) updateCameraTranslation(cTransform.getTranslation().x, -0.5f, 1, -moveSpeed, true);
	else if (sceneContext.input->isKeyDown(KEY_D)) updateCameraTranslation(cTransform.getTranslation().x, (BOARD_WIDTH - 1) + 0.5f, -1, moveSpeed, true);

	     if (sceneContext.input->isKeyDown(KEY_W)) updateCameraTranslation(cTransform.getTranslation().y, (BOARD_HEIGHT - 1) + 0.5f, -1, moveSpeed, false);
	else if (sceneContext.input->isKeyDown(KEY_S)) updateCameraTranslation(cTransform.getTranslation().y, -0.5f,  1, -moveSpeed, false);

	if (!sceneContext.input->isMouseScrolled()) return;

	if ((sceneContext.input->getMouseScroll() > 0 && getBoundCamera().projection.getFOV() > MAX_ZOOM_IN) ||
		(sceneContext.input->getMouseScroll() < 0 && getBoundCamera().projection.getFOV() < MAX_ZOOM_OUT))
		getBoundCamera().projection.offsetFOV(scrollSpeed * -sceneContext.input->getMouseScroll());
}

void GameScene::updateCameraTranslation(float xy, float bound, int8_t mul, double speed, bool xAxis)
{
	if (xy * mul > bound * mul) {
		if ((xy + speed) * mul <= bound * mul)
			getBoundCamera().transform.setTranslation(xAxis ? glm::vec3{ bound, getBoundCamera().transform.getTranslation().y, 0.0f} : glm::vec3{ getBoundCamera().transform.getTranslation().x, bound, 0.0f });
		else
			getBoundCamera().transform.offsetTranslation({ speed * xAxis, speed * (!xAxis), 0.0f});
	}
}

void GameScene::updateChoice()
{
	     if (sceneContext.input->isKeyPressed(KEY_1)) m_currentColor = START_COLOR;
	else if (sceneContext.input->isKeyPressed(KEY_2)) m_currentColor = END_COLOR;
	else if (sceneContext.input->isKeyPressed(KEY_3)) m_currentColor = BLOCK_COLOR;
}

void GameScene::updateBoard()
{
	static glm::vec2 lastMousePos{ 0.0f, 0.0f };

	if (m_board.isCellEmpty(lastMousePos.x, lastMousePos.y)) m_board.unsetCell(lastMousePos.x, lastMousePos.y);

	glm::vec2 worldMousePos = screenToWorldSpace(sceneContext.input->getMousePos(), engine::RenderCommand::getWindowSize(), getBoundCamera().getViewProjectionMatrix()) + 0.5f;
	if (!(worldMousePos.x > 0.0f && worldMousePos.x < BOARD_WIDTH && worldMousePos.y > 0.0f && worldMousePos.y < BOARD_HEIGHT && !m_disableMouseInput)) return;

	if (sceneContext.input->isMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		m_board.unsetCell(worldMousePos.x, worldMousePos.y);
	}

	if (m_board.isCellEmpty(worldMousePos.x, worldMousePos.y)) {
		m_board.hoverCell(worldMousePos.x, worldMousePos.y, m_currentColor * 0.7f);
	}

	if (sceneContext.input->isMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		if (m_currentColor == START_COLOR)
			m_board.setStartCell(worldMousePos.x, worldMousePos.y, m_currentColor);
		else if (m_currentColor == END_COLOR)
			m_board.setEndCell(worldMousePos.x, worldMousePos.y, m_currentColor);
		else if (m_currentColor == BLOCK_COLOR)
			m_board.setBlockCell(worldMousePos.x, worldMousePos.y, m_currentColor);
	}

	lastMousePos = worldMousePos;
}

void GameScene::changeState()
{
	if (sceneContext.input->isKeyPressed(KEY_SPACE)) {
		if (m_disableMouseInput) {
			initBoard();
			m_disableMouseInput = false;
			return;
		}

		if (m_board.computePath(PATH_COLOR)) {
			m_disableMouseInput = true;
		}
	}
}

void GameScene::onUpdate(double dT)
{
	updateCamera(dT);
	updateChoice();
	updateBoard();
	changeState();
}

void GameScene::onRender()
{
	engine::RenderCommand::clear(GL_COLOR_BUFFER_BIT);

	sceneContext.renderer2D->beginScene(&getBoundCamera());

	m_board.render(sceneContext);

	sceneContext.renderer2D->endScene();
}
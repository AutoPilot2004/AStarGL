#include "FadeScene.h"

#include <engine/Renderer/RenderCommand.h>

#define FADE_SPEED 0.0015f

FadeScene::FadeScene(const engine::SceneContext& sceneContext, const std::function<void()>& fadeInCompleteCallback, const std::function<void()>& fadeOutCompleteCallback)
	: engine::Scene(sceneContext), m_fadeInCompleteCallback(fadeInCompleteCallback), m_fadeOutCompleteCallback(fadeOutCompleteCallback)
{
	m_shader.create("../Shaders/FadeShader.vert", "../Shaders/FadeShader.frag");
}

void FadeScene::onEntry()
{

}

void FadeScene::onExit()
{

}

void FadeScene::onUpdate(double dT)
{
	if (m_fading) {
		m_time += FADE_SPEED * m_timeMul * dT;
		if (m_time >= 1.0f) {
			m_fading = false;
			m_time = 1.0f;
			updateShaderTime();
			m_fadeOutCompleteCallback();
		}
		else if (m_time <= 0.0f) {
			m_fading = false;
			m_time = 0.0f;
			updateShaderTime();
			m_fadeInCompleteCallback();
		}
	}
}

void FadeScene::onRender()
{
	if (m_fading) updateShaderTime();

	sceneContext.renderer2D->renderBufferlessVertices(3, m_shader);
}

void FadeScene::fadeIn()
{
	m_fading = true;
	m_timeMul = -1;
}

void FadeScene::fadeOut()
{
	m_fading = true;
	m_timeMul = 1;
}

void FadeScene::updateShaderTime()
{
	m_shader.bind();
	m_shader.setFloat("time", m_time);
}
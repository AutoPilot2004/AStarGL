#pragma once
#include <engine/Scene/Scene.h>
#include <engine/Graphics/Shader.h>

class FadeScene : public engine::Scene
{
public:
	FadeScene(const engine::SceneContext& sceneContext, const std::function<void()>& fadeInCompleteCallback, const std::function<void()>& fadeOutCompleteCallback);

	void onEntry()           override;
	void onExit()            override;

	void onUpdate(double dT) override;
	void onRender()          override;

	void fadeIn();
	void fadeOut();

private:
	void updateShaderTime();

private:
	engine::Shader m_shader;

	float m_time = 0.0f;
	int8_t m_timeMul = 1;
	bool m_fading = false;

	std::function<void()> m_fadeInCompleteCallback;
	std::function<void()> m_fadeOutCompleteCallback;
};
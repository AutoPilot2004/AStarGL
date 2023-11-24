#include <iostream>
#include "engine/Window/Window.h"
#include "engine/Graphics/VertexBuffer.h"
#include "engine/Graphics/ElementBuffer.h"
#include "engine/Graphics/Shader.h"
#include "engine/Shapes/Shapes.h"
#include "engine/Renderer/Renderer2D.h"
#include "engine/Scene/Camera2D.h"
#include "engine/Management/Textures/TextureManager.h"

#include <chrono>
#include <GLFW/glfw3.h>

//#define CELL_SIZE 15.0f

float CELL_SIZE = 3.f;

double offX=0, offY=0;

#define WIDTH 1920
#define HEIGHT 1080

void moCallback(const engine::MouseScrollEvent& e)
{
	offY = e.offset;
}

glm::vec4 ScreenToWorld(const glm::vec2& mousePos, const glm::mat4& pv)
{
	glm::vec2 res;

	res.x = 2 * mousePos.x / WIDTH - 1;
	res.y = 2 * (mousePos.y) / HEIGHT - 1;

	glm::vec4 screen_space_mouse = glm::vec4(res, 1.f, 1);

	screen_space_mouse = glm::inverse(pv) * screen_space_mouse;

	screen_space_mouse /= screen_space_mouse.w;
	glm::vec4 m_world_space_mouse = screen_space_mouse;

	return m_world_space_mouse;
}

int main()
{
	//TODO: LOGGING EVERYWHERE

	engine::init();

	engine::WindowSettings settings;
	settings.title = "YOO";
	settings.width = WIDTH;
	settings.height = HEIGHT;

	engine::Window window;
	window.setSettings(settings);
	window.create();

	glfwSwapInterval(0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_MULTISAMPLE);

	void* b = window.eventManager.dispatcher.addListener<engine::MouseScrollEvent>(moCallback);

	engine::Shader defaultShader;
	defaultShader.create("Shaders/QuadShader.vert", "Shaders/QuadShader.frag");
	engine::Shader defaultShader2;
	defaultShader2.create("Shaders/QuadShader.vert", "Shaders/QuadShader.frag");
	engine::Shader defaultShader3;
	defaultShader3.create("Shaders/QuadShader.vert", "Shaders/QuadShader.frag");

	engine::Shader gridShader;
	gridShader.create("Shaders/GridShader.vert", "Shaders/GridShader.frag");

	engine::Rect rect;
	rect.transform.translation = {0.0f, 0.0f, 0.9f};
	rect.transform.rotation = (0.0f);
	rect.transform.scale = glm::vec2{ CELL_SIZE - 2.5f };
	rect.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	rect.shader = &defaultShader;
	rect.rounding = 1.0;

	engine::Rect rect2;
	rect2.transform.translation = { 0.0f, 0.0f, 0.0f };
	rect2.transform.rotation = (0.0f);
	rect2.transform.scale = { 5.0f, 5.0f };
	rect2.color = { 1.0f, 0.0f, 1.0f, 1.f };
	rect2.shader = &defaultShader2;
	rect2.rounding = 0.8f;

	engine::Rect rect3;
	rect3.transform.translation = { 0.0f, 0.4f, 0.0f };
	rect3.transform.rotation = (0.0f);
	rect3.transform.scale = { 0.1f, 0.1f };
	rect3.color = { 1.0f, 0.0f, 1.0f, 1.0f };
	rect3.shader = &defaultShader3;
	rect3.rounding = 0.4f;

	engine::TextureManager texMan;
	engine::Circle ellipse;
	ellipse.shader = &defaultShader2;
	ellipse.transform.translation = { 0.0f, 1.0f, 0.0 };
	ellipse.radius = CELL_SIZE - 2.5f;

	/*for (uint32_t j = 0; j < 12'500/2; j++) {
		rect.transform.rotation = 0.0f;
		for (float i = -1.0f; i < 1.0f; i += CELL_SIZE) {
			rect.transform.translation.x = i;
			renderer.drawRect(rect, true);
		}
		rect.transform.translation.x = 0.0f;
		rect.transform.rotation = 90.0f;
		for (float i = -1.0f; i < 1.0f; i += CELL_SIZE) {
			rect.transform.translation.y = i+j/1000.0f;
			renderer.drawRect(rect, true);
		}
	}*/

	engine::Camera2D cam(window, 1.0f);

	
	

	//renderer.drawCircle(ellipse, true);

	rect.texture.textureInfo = texMan.getTextureInfo("a.png");
	engine::Renderer2D renderer(texMan);
	{
		glClearColor(1.3f, 0.3f, 0.3f, 1.0f);
		defaultShader.bind();

		while (!window.isClosed()) {
			//static float count;
			//count += 0.5f;
			//rect.transform.setRotation(count);
			/*glm::vec2 mousePos = window.eventManager.input.getMousePos();
			mousePos.y = window.getSettings().height - mousePos.y;
			mousePos /= glm::vec2(window.getSettings().width, window.getSettings().height);
			mousePos *= 2.0f;
			mousePos -= 1.0f;

			INFO_LOG("MOUSEPOS: {},{}\n", mousePos.x, mousePos.y);
			if (mousePos.x < rect.transform.translation.x + rect.transform.scale.x / 2.0f &&
				mousePos.x > rect.transform.translation.x - rect.transform.scale.x / 2.0f &&
				mousePos.y < rect.transform.translation.y + rect.transform.scale.y / 2.0f &&
				mousePos.y > rect.transform.translation.y - rect.transform.scale.y / 2.0f)
				rect.color = glm::vec4(0.0f, 0.0f, 1.0f, 0.3f);
			else
				rect.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);*/

			//glm::vec4 mPStart = ScreenToWorld(glm::vec2{ 0.0f }, cam.projection.getProjectionMatrix() * glm::inverse(cam.transform.getTransformMatrix()));
			//glm::vec4 mPEnd = ScreenToWorld(glm::vec2{ WIDTH, HEIGHT }, cam.projection.getProjectionMatrix() * glm::inverse(cam.transform.getTransformMatrix()));
			////INFO_LOG("{} {}\n", mPStart.x, mPStart.y)

			/*if (window.eventManager.input.isKeyDown(KEY_D) && mPEnd.x < 100.0f) cam.transform.setTranslation(cam.transform.getTranslation() - glm::vec3{ 0.0375f/3.0, 0.0f, 0.0f });
			if (window.eventManager.input.isKeyDown(KEY_A) && mPStart.x > -100.0f) cam.transform.setTranslation(cam.transform.getTranslation() + glm::vec3{ 0.0375f/3, 0.0f, 0.0f });
			if (window.eventManager.input.isKeyDown(KEY_W) && mPEnd.y < 100.0f) cam.transform.setTranslation(cam.transform.getTranslation() - glm::vec3{ 0.0f, 0.0375f/3, 0.0f });
			if (window.eventManager.input.isKeyDown(KEY_S) && mPStart.y > -100.0f) cam.transform.setTranslation(cam.transform.getTranslation() + glm::vec3{ 0.0f, 0.0375f/3, 0.0f });
			cam.projection.setFOV(cam.projection.getFOV() - offY * 0.3f);*/
	
			//if (window.eventManager.input.isKeyDown(KEY_E)) { cam.transform.setScale(cam.transform.getScale() + glm::vec2{ 0.02 }); }

			if (window.eventManager.input.isKeyDown(KEY_W)) cam.transform.setTranslation(cam.transform.getTranslation() + glm::vec3(0.0f, -0.1f, 0.0f));
			if (window.eventManager.input.isKeyDown(KEY_E)) cam.transform.setTranslation(cam.transform.getTranslation() + glm::vec3(0.0f, 0.0f, -0.1f));
			if (window.eventManager.input.isKeyDown(KEY_A) && cam.transform.getTranslation().x < 10.0f) cam.transform.setTranslation(cam.transform.getTranslation() + glm::vec3(0.001f, 0.0f, 0.0f));
			if (window.eventManager.input.isKeyDown(KEY_D) && cam.transform.getTranslation().x > 0.0f) cam.transform.setTranslation(cam.transform.getTranslation() + glm::vec3(-0.001f, 0.0f, 0.0f));

			cam.projection.setFOV(cam.projection.getFOV() - offY);
		
			auto start = std::chrono::high_resolution_clock::now();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//ellipse.color = glm::vec4(glm::vec3(sin(std::chrono::high_resolution_clock::now().time_since_epoch().count())),1.0f);
			renderer.beginScene(&cam);
			/*rect.transform.translation.x = 0.0f;
			rect.transform.translation.y = 0.0f;
			rect.transform.rotation = 0.0f;
			rect.texture.uv = { 0.7, 0.7, 2.0, 2.0 };*/
			renderer.drawCircle(ellipse);
			//for (uint32_t i = 0; i < 1'000'000; i++)
			renderer.drawCircle(ellipse);
			//renderer.drawRect(rect2);
			//renderer.drawRect(rect2);
			//renderer.drawRect(rect);
			renderer.endScene();
			glDisable(GL_DEPTH_TEST);
			gridShader.bind();
			gridShader.setFloat("pov", cam.projection.getFOV());
			gridShader.setVec3("camPos", cam.transform.getTranslation());
			gridShader.setMat4("viewMat", cam.transform.getTransformMatrix());
			gridShader.setMat4("projMat", cam.projection.getProjectionMatrix());
			renderer.renderBufferlessVertices(3, gridShader);
			glEnable(GL_DEPTH_TEST);
			offX = 0;
			offY = 0;

			window.update();

			auto dur = std::chrono::high_resolution_clock::now() - start;
			INFO_LOG("FrameTime: {}ms\n", 1'000.0f / (dur.count() / 1'000'000.0f));
		}
	}

	engine::destroy();

	window.eventManager.dispatcher.removeListener<engine::MouseScrollEvent>(b);

	std::cin.get();

	return 0;
}
#pragma once
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

#include "Graphics/ShaderStorageBuffer.h"
#include "Graphics/ElementBuffer.h"
#include "Graphics/VertexArray.h"

namespace engine
{
	struct Shape;

	class Camera2D;
	class Shader;

	namespace _impl
	{
		struct Quad
		{
			glm::vec4 translationTexHandleIdx;
			glm::vec4 rotationScaleRounding;
			glm::vec4 uv;
			glm::vec4 color;
		};

		struct SSBOData
		{
			void drawShape(const Shape& shape, const auto& textureMap, bool isRect);
			void fillSSBO();
			void render(const glm::mat4& viewProj);

			ShaderStorageBuffer ssbo;
			std::unordered_map<const Shader*, std::vector<_impl::Quad>> quadsMap;
			std::unordered_map<GLuint, GLintptr> ssboShaderOffset;
			uint64_t totalSize = 0;
		};
	}

	struct Rect;
	struct Circle;

	class TextureManager;

	class Renderer2D
	{
	public:
		Renderer2D(TextureManager& textureManager);
		~Renderer2D();

		void beginScene(Camera2D* camera);
		void endScene();
		void renderBufferlessVertices(GLsizei count, const Shader& shader);

		void drawRect(const Rect& rect, bool isStatic = false);
		void drawCircle(const Circle& circle, bool isStatic = false);

	private:
		Renderer2D(const Renderer2D&) = delete;
		Renderer2D(Renderer2D&&) = delete;
		Renderer2D& operator=(const Renderer2D&) = delete;
		Renderer2D& operator=(Renderer2D&&) = delete;

	private:
		void init(TextureManager& textureManager);
		void restart();

		void renderScene();

		void drawShape(const Shape& shape, bool isStatic, bool isRect);

	private:
		VertexArray m_vao;
		ElementBuffer m_ebo;

		_impl::SSBOData m_staticSSBO;
		_impl::SSBOData m_dynamicSSBO;

		ShaderStorageBuffer m_textureSSBO;
		std::vector<GLuint64> m_textureHandles;
		std::unordered_map<GLuint64, uint32_t> m_textureMap;

		Camera2D* m_boundCamera = nullptr;

		bool m_staticUploaded = false;
		bool m_restarting = false;
	};
}
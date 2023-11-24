#include "Renderer2D.h"

#include "Core.h"
#include "Shapes/Shapes.h"
#include "Scene/Camera2D.h"
#include "Management/Textures/TextureManager.h"

#define MAX_DYNAMIC_SSBO_COUNT 3'500
#define MAX_QUADS_COUNT 500'000
#define MAX_SIZE_FOR(x) MAX_DYNAMIC_SSBO_COUNT * sizeof(x)

namespace engine
{
	namespace _impl
	{
		void SSBOData::drawShape(const Shape& shape, const auto& textureMap, bool isRect)
		{
			quadsMap[shape.shader].emplace_back(glm::vec4{ shape.transform.translation, shape.texture.textureInfo ? textureMap.at(shape.texture.textureInfo->handle) : 0 },
												glm::vec4{ shape.transform.rotation,
												isRect ? static_cast<const Rect&>(shape).transform.scale : glm::vec2{ static_cast<const Circle&>(shape).radius },
												isRect ? static_cast<const Rect&>(shape).rounding : 1.0f },
												shape.texture.uv,
												shape.color);

			totalSize++;
		}

		void SSBOData::fillSSBO()
		{
			GLintptr offset = 0;

			for (const auto& [shader, vec] : quadsMap) {
				ssboShaderOffset[shader->getID()] = offset;
				ssbo.fill(ssboShaderOffset.at(shader->getID()), vec.size() * sizeof(vec[0]), vec.data());
				offset += vec.size() * sizeof(vec[0]);
			}
		}

		void SSBOData::render(const glm::mat4& viewProj)
		{
			for (const auto& [shader, vec] : quadsMap) {
				shader->bind();
				shader->setMat4("viewProj", viewProj);
				ssbo.bindBaseRange(0, ssboShaderOffset.at(shader->getID()), vec.size() * sizeof(vec[0]));

				glDrawElements(GL_TRIANGLES, vec.size() * 6, GL_UNSIGNED_INT, nullptr);
			}
		}
	}

	Renderer2D::Renderer2D(TextureManager& textureManager)
	{
		init(textureManager);
	}

	Renderer2D::~Renderer2D()
	{
		for (auto handle : m_textureHandles)
			glMakeTextureHandleNonResidentARB(handle);
	}

	void Renderer2D::init(TextureManager& textureManager)
	{
		m_dynamicSSBO.ssbo.allocStaticForDraw<BufferFlags::DYNAMIC_STORAGE>(MAX_SIZE_FOR(_impl::Quad));

		std::vector<uint32_t> indices;

		for (uint32_t i = 0; i < MAX_QUADS_COUNT; i++) {
			indices.push_back(i*4 + 0);
			indices.push_back(i*4 + 1);
			indices.push_back(i*4 + 2);
			indices.push_back(i*4 + 2);
			indices.push_back(i*4 + 3);
			indices.push_back(i*4 + 0);
		}

		m_vao.bind();
		m_ebo.bind();
		m_ebo.allocStaticForDrawAndFill<BufferFlags::NONE>(indices.size() * sizeof(indices[0]), indices.data());

		uint32_t texIdx = 1;
		
		m_textureHandles.push_back(textureManager.getWhiteTextureInfo()->handle);
		for (const auto& [str, texInfo] : textureManager.getTextureMap()) {
			glMakeTextureHandleResidentARB(texInfo.handle);
			m_textureHandles.push_back(texInfo.handle);
			m_textureMap[texInfo.handle] = texIdx++;
		}

		m_textureSSBO.allocStaticForDrawAndFill<BufferFlags::NONE>(m_textureHandles.size() * sizeof(m_textureHandles[0]), m_textureHandles.data());
		m_textureSSBO.bindBase(1);
	}
	
	void Renderer2D::restart()
	{
		m_restarting = true;
		endScene();
		beginScene(m_boundCamera);
		m_restarting = false;
	}

	void Renderer2D::beginScene(Camera2D* camera)
	{
		for (auto& [id, vec] : m_dynamicSSBO.quadsMap) {
			vec.clear();
		}

		m_dynamicSSBO.totalSize = 0;

		m_boundCamera = camera;
	}

	void Renderer2D::endScene()
	{
		m_dynamicSSBO.fillSSBO();

		if (!m_staticUploaded && !m_restarting) {
			m_staticSSBO.ssbo.allocStaticForDraw<BufferFlags::DYNAMIC_STORAGE>(m_staticSSBO.totalSize * sizeof(_impl::Quad));
			m_staticSSBO.fillSSBO();
			m_staticUploaded = true;
		}

		renderScene();
	}

	void Renderer2D::renderBufferlessVertices(GLsizei count, const Shader& shader)
	{
		m_vao.bind();
		shader.bind();
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void Renderer2D::renderScene()
	{
		m_vao.bind();
		
		const glm::mat4& viewProj = m_boundCamera->getViewProjectionMatrix();

		m_dynamicSSBO.render(viewProj);

		if (!m_restarting) {
			m_staticSSBO.render(viewProj);
		}
	}

	void Renderer2D::drawShape(const Shape& shape, bool isStatic, bool isRect)
	{
		if (isStatic) {
			if (m_staticUploaded)                          { WARN_LOG("Static Data cannot be modified!\n") return; }
			if (m_staticSSBO.totalSize >= MAX_QUADS_COUNT) { WARN_LOG("Max Quad Count Reached!\n")         return; }

			m_staticSSBO.drawShape(shape, m_textureMap, isRect);

			return;
		}

		if (m_dynamicSSBO.totalSize >= MAX_DYNAMIC_SSBO_COUNT) restart();

		m_dynamicSSBO.drawShape(shape, m_textureMap, isRect);
	}

	void Renderer2D::drawRect(const Rect& rect, bool isStatic /* = false */)
	{
		drawShape(rect, isStatic, true);
	}

	void Renderer2D::drawCircle(const Circle& circle, bool isStatic /* = false */)
	{
		drawShape(circle, isStatic, false);
	}
}
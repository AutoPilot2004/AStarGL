#pragma once
#include <cstdint>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace engine
{
	struct TextureInfo
	{
		GLuint id;
		GLuint64 handle;
		uint16_t width;
		uint16_t height;
		uint8_t channels;
	};

	struct Texture
	{
		const TextureInfo* textureInfo = nullptr;
		glm::vec4 uv{ 0.0f, 0.0f, 1.0f, 1.0f };
	};
}
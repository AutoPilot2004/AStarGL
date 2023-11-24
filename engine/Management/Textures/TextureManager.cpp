#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Core.h"

#define WHITE_TEXTURE_KEY "whiteTexture_impl_engine_45632"


namespace engine
{
	TextureManager::~TextureManager()
	{
		for (const auto& [str, texInfo] : m_textureMap)
			glDeleteTextures(1, &texInfo.id);
	}

	const TextureInfo* TextureManager::getTextureInfo(const std::string& path)
	{
		if (m_textureMap.find(path) == m_textureMap.end()) {
			int w, h, c;

			stbi_set_flip_vertically_on_load(1);
			unsigned char* imageData = stbi_load(path.c_str(), &w, &h, &c, 4);

			if (!imageData) {
				ERROR_LOG("Couldn't load texture in: {}\n", path.c_str());
				return nullptr;
			}

			uploadTexture(path, w, h, c, imageData);

			stbi_image_free(imageData);
		}

		return &m_textureMap.at(path);
	}

	const TextureInfo* TextureManager::getWhiteTextureInfo()
	{
		if (m_textureMap.find(WHITE_TEXTURE_KEY) == m_textureMap.end()) {
			uint32_t whiteColor = 0xffffffff;

			uploadTexture(WHITE_TEXTURE_KEY, 1, 1, 4, &whiteColor);
		}

		return &m_textureMap.at(WHITE_TEXTURE_KEY);
	}

	void TextureManager::uploadTexture(const std::string& path, uint16_t width, uint16_t height, uint8_t channels, const void* pixels)
	{
		TextureInfo texInfo{
				.width = width,
				.height = height,
				.channels = channels
		};

		glGenTextures(1, &texInfo.id);
		glBindTexture(GL_TEXTURE_2D, texInfo.id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texInfo.width, texInfo.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		texInfo.handle = glGetTextureHandleARB(texInfo.id);

		glBindTexture(GL_TEXTURE_2D, 0);

		m_textureMap[path] = texInfo;
	}
}
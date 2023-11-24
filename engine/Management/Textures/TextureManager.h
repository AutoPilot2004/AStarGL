#pragma once
#include <string>
#include <unordered_map>

#include "Graphics/Texture.h"

namespace engine
{
	class TextureManager
	{
	public:
		TextureManager() = default;
		~TextureManager();

		const TextureInfo* getTextureInfo(const std::string& path);

		const auto& getTextureMap() const { return m_textureMap; }

	private:
		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager& operator=(TextureManager&&) = delete;

	private:
		const TextureInfo* getWhiteTextureInfo();
		void uploadTexture(const std::string& path, uint16_t width, uint16_t height, uint8_t channels, const void* pixels);

	private:
		std::unordered_map<std::string, TextureInfo> m_textureMap;

		friend class Renderer2D;
	};
}
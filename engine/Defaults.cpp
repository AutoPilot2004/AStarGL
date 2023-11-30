#include "Defaults.h"

#include "Graphics/Shader.h"

#include <unordered_map>

#define QUAD_SHADER_ID 1
#define QUAD_SHADER_VERT_PATH "../Shaders/QuadShader.vert"
#define QUAD_SHADER_FRAG_PATH "../Shaders/QuadShader.frag"

namespace
{
	std::unordered_map<uint32_t, engine::Shader> m_shaderMap;
}

namespace engine
{
	namespace Defaults
	{
		[[nodiscard]] const Shader* getQuadShader()
		{
			if (m_shaderMap.find(QUAD_SHADER_ID) == m_shaderMap.end()) {
				Shader shader(QUAD_SHADER_VERT_PATH, QUAD_SHADER_FRAG_PATH);

				m_shaderMap[QUAD_SHADER_ID] = shader;
			}

			return &m_shaderMap.at(QUAD_SHADER_ID);
		}
	}
}
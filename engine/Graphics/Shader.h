#pragma once
#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace engine
{
	class Shader
	{
	public:
		void create(const std::string& vertFilePath, const std::string& fragFilePath);

		       void bind() const;
		static void bind(GLuint program);
		static void unbind();

		void setFloat(const std::string& name, float value) const;
		void setVec3(const std::string& name, const glm::vec3& vec3) const;
		void setMat4(const std::string& name, const glm::mat4& mat4) const;

		//Getters
		inline GLuint getID() const { return m_id; }

	private:
		GLint getLocation(const std::string& name) const;

	private:
		GLuint m_id;

		mutable std::unordered_map<std::string, GLint> m_uniformMap;
	};
}
#include "Shader.h"

#include <vector>
#include <fstream>

#include "Core.h"

namespace
{
	GLuint createShader(const std::string& filePath, GLenum shaderType)
	{
		GLuint id = glCreateShader(shaderType);
		
		std::string contents;
		std::string line;

		std::ifstream file(filePath);

		while (std::getline(file, line)) {
			contents += line + '\n';
		}

		const GLchar* contentsPtr = contents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);
		glCompileShader(id);

		GLint isCompiled = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(id);

			FATAL_ERROR("Couldn't compile shader: {}\nError: {}\n", filePath, errorLog.data());
		}

		return id;
	}

	GLuint createAndLinkProgram(GLuint vertID, GLuint fragID)
	{
		GLuint program = glCreateProgram();
		glAttachShader(program, vertID);
		glAttachShader(program, fragID);
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertID);
			glDeleteShader(fragID);

			FATAL_ERROR("Couldn't link program!\nError: {}\n", errorLog.data());
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertID);
		glDetachShader(program, fragID);

		return program;
	}
}

namespace engine
{
	void Shader::create(const std::string& vertFilePath, const std::string& fragFilePath)
	{
		GLuint vertID = createShader(vertFilePath, GL_VERTEX_SHADER);
		GLuint fragID = createShader(fragFilePath, GL_FRAGMENT_SHADER);

		m_id = createAndLinkProgram(vertID, fragID);
	}

	void Shader::bind() const
	{
		bind(m_id);
	}

	void Shader::bind(GLuint program)
	{
		glUseProgram(program);
	}

	void Shader::unbind()
	{
		bind(0);
	}

	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(getLocation(name), value);
	}

	void Shader::setVec3(const std::string& name, const glm::vec3& vec3) const
	{
		glUniform3f(getLocation(name), vec3.x, vec3.y, vec3.z);
	}

	void Shader::setMat4(const std::string& name, const glm::mat4& mat4) const
	{
		glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, &mat4[0][0]);
	}

	GLint Shader::getLocation(const std::string& name) const
	{
		if (m_uniformMap.find(name) == m_uniformMap.end())
			m_uniformMap[name] = glGetUniformLocation(m_id, name.c_str());

		return m_uniformMap.at(name);
	}
}
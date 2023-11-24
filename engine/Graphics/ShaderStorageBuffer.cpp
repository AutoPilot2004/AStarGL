#include "ShaderStorageBuffer.h"

namespace engine
{
	ShaderStorageBuffer::ShaderStorageBuffer()
		: Buffer(GL_SHADER_STORAGE_BUFFER)
	{}

	void ShaderStorageBuffer::bindBase(GLuint index)
	{
		glBindBufferBase(m_type, index, m_id);
	}

	void ShaderStorageBuffer::bindBaseRange(GLuint index, GLintptr offset, GLsizeiptr size)
	{
		glBindBufferRange(m_type, index, m_id, offset, size);
	}
}
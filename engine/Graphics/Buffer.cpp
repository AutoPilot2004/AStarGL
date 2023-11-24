#include "Buffer.h"

namespace engine
{
	Buffer::Buffer(GLenum type)
		: m_type(type)
	{
		glCreateBuffers(1, &m_id);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void Buffer::bind() const
	{
		glBindBuffer(m_type, m_id);
	}

	void Buffer::unbind() const
	{
		glBindBuffer(m_type, 0);
	}

	void Buffer::fill(GLintptr offset, GLsizeiptr size, const void* data) const
	{
		glNamedBufferSubData(m_id, offset, size, data);
	}
}
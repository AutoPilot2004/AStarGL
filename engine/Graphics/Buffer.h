#pragma once

#include <GL/glew.h>

namespace engine
{
	enum class DrawType
	{
		STATIC  =  GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW
	};

	enum class BufferFlags
	{
		NONE            = 0,
		DYNAMIC_STORAGE = GL_DYNAMIC_STORAGE_BIT
	};

	class Buffer
	{
	public:
		void bind() const;
		void unbind() const;

		template<DrawType drawType>
		void allocDynamicForDraw(GLsizeiptr size) const
		{
			glNamedBufferData(m_id, size, nullptr, static_cast<GLenum>(drawType));
		}

		template<DrawType drawType>
		void allocDynamicForDrawAndFill(GLsizeiptr size, const void* data) const
		{
			glNamedBufferData(m_id, size, data, static_cast<GLenum>(drawType));
		}

		template<BufferFlags bufferFlags>
		void allocStaticForDraw(GLsizeiptr size) const
		{
			glNamedBufferStorage(m_id, size, nullptr, static_cast<GLbitfield>(bufferFlags));
		}

		template<BufferFlags bufferFlags>
		void allocStaticForDrawAndFill(GLsizeiptr size, const void* data) const
		{
			glNamedBufferStorage(m_id, size, data, static_cast<GLbitfield>(bufferFlags));
		}

		void fill(GLintptr offset, GLsizeiptr size, const void* data) const;

	protected:
		Buffer(GLenum type);
		~Buffer();

	protected:
		GLuint m_id;
		GLenum m_type;

	private:
		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) = delete;
		Buffer& operator=(const Buffer&) = delete;
		Buffer& operator=(Buffer&&) = delete;
	};
}
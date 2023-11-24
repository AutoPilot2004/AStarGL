#pragma once
#include "Buffer.h"

namespace engine
{
	class ShaderStorageBuffer : public Buffer
	{
	public:
		ShaderStorageBuffer();

		void bindBase(GLuint index);
		void bindBaseRange(GLuint index, GLintptr offset, GLsizeiptr size);

	private:
	};
}
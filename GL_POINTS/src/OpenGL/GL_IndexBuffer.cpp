#include "GL_IndexBuffer.h"

#include <iostream>

#include "GL_gl.h"

namespace OpenGL
{
	IndexBuffer::IndexBuffer()
		:
		m_indice_count(0)
	{
		glGenBuffers(1, &m_id);
	}

	IndexBuffer::IndexBuffer(uint32_t* indices, const uint32_t& count)
	{
		glGenBuffers(1, &m_id);

		m_indice_count = count;

		bind();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_DYNAMIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void IndexBuffer::create(uint32_t* indices, const uint32_t& count)
	{
		m_indice_count = count;

		bind();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_DYNAMIC_DRAW);
	}

	void IndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	uint32_t IndexBuffer::getIndiceCount() const
	{
		return m_indice_count;
	}
}


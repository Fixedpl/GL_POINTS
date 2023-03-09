#include "GL_VertexBuffer.h"

#include <cassert>

namespace OpenGL
{
	uint32_t VertexAttributeElement::getTypeSize(const uint32_t& data_type)
	{
		switch (data_type) {
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		}

		return 0;
	}

	const std::vector<VertexAttributeElement>& BufferLayout::getAttributeElements() const
	{
		return m_va_elements;
	}

	uint32_t BufferLayout::getStride() const
	{
		return m_stride;
	}

	void BufferLayout::_addAttribute(const uint32_t& vertex_dim, const uint32_t& data_type) {
		uint32_t data_type_size = VertexAttributeElement::getTypeSize(data_type);
		m_va_elements.push_back({ vertex_dim, data_type });
		m_stride += vertex_dim * data_type_size;
	}



	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &m_id);
	}

	VertexBuffer::VertexBuffer(const uint32_t& size, const DrawType& draw_type)
	{
		glGenBuffers(1, &m_id);

		bind();

		glBufferData(GL_ARRAY_BUFFER, size, nullptr, static_cast<GLenum>(draw_type));
	}

	VertexBuffer::VertexBuffer(void* data, const uint32_t& size, const DrawType& draw_type)
	{
		glGenBuffers(1, &m_id);

		bind();

		glBufferData(GL_ARRAY_BUFFER, size, data, static_cast<GLenum>(draw_type));
	}


	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void VertexBuffer::create(const uint32_t& size, const DrawType& draw_type) const
	{
		bind();

		glBufferData(GL_ARRAY_BUFFER, size, nullptr, static_cast<GLenum>(draw_type));
	}


	void VertexBuffer::update(void* data, const uint32_t& size, const uint32_t& offset)
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}



	VertexArray::VertexArray()
		:
		m_index_buffer(nullptr)
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::bind() const {
		glBindVertexArray(m_id);
	}

	void VertexArray::addVertexBuffer(VertexBuffer* vertex_buffer)
	{
		bind();
		vertex_buffer->bind();

		m_vertex_buffers.push_back(vertex_buffer);
	}

	const IndexBuffer& VertexArray::getIndexBuffer() const
	{
		assert(m_index_buffer);
		return *m_index_buffer;
	}

	void VertexArray::setIndexBuffer(IndexBuffer* index_buffer)
	{
		bind();
		index_buffer->bind();

		m_index_buffer = index_buffer;
	}

	BufferLayout VertexArray::getBufferLayout() const
	{
		return m_buffer_layout;
	}

	void VertexArray::setBufferLayout(const BufferLayout& buffer_layout)
	{
		m_buffer_layout = buffer_layout;

		bind();

		const auto& vertex_attributes = m_buffer_layout.getAttributeElements();
		uint32_t offset = 0;
		for (int i = 0; i < vertex_attributes.size(); i++) {
			const auto& attribute = vertex_attributes[i];
			glVertexAttribPointer(i, attribute.vertex_dim, attribute.data_type, GL_FALSE, m_buffer_layout.getStride(), (const void*)offset);
			glEnableVertexAttribArray(i);
			offset += (attribute.vertex_dim * VertexAttributeElement::getTypeSize(attribute.data_type));
		}
	}

}


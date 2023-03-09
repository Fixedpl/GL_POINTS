#pragma once
#include <cstdint>
#include <vector>
#include <cassert>

#include "GL_IndexBuffer.h"
#include "GL_DrawTypeEnum.h"
#include "GL_gl.h"


namespace OpenGL
{
	struct VertexAttributeElement {
		uint32_t vertex_dim;
		uint32_t data_type;

		static uint32_t getTypeSize(const uint32_t& data_type);
	};



	class BufferLayout
	{
	public:

		template <typename T>
		void addAttribute(const uint32_t& vertex_dim);

		const std::vector<VertexAttributeElement>& getAttributeElements() const;

		uint32_t getStride() const;

	private:

		void _addAttribute(const uint32_t& vertex_dim, const uint32_t& data_type);

	private:

		std::vector<VertexAttributeElement> m_va_elements;

		uint32_t m_stride;

	};



	class VertexBuffer
	{
	public:

		VertexBuffer();
		VertexBuffer(const uint32_t& size, const DrawType& draw_type);
		VertexBuffer(void* data, const uint32_t& size, const DrawType& draw_type);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer& obj) = delete;
		VertexBuffer& operator=(const VertexBuffer& obj) = delete;

		VertexBuffer(VertexBuffer&& obj) = delete;
		VertexBuffer& operator=(VertexBuffer&& obj) = delete;

		void bind() const;

		void create(const uint32_t& size, const DrawType& draw_type) const;

		void update(void* data, const uint32_t& size, const uint32_t& offset);

	private:

		uint32_t m_id;

	};



	class VertexArray
	{
	public:

		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray& obj) = delete;
		VertexArray& operator=(const VertexArray& obj) = delete;

		VertexArray(VertexArray&& obj) = delete;
		VertexArray& operator=(VertexArray&& obj) = delete;

		void bind() const;

		void addVertexBuffer(VertexBuffer* vertex_buffer);

		const IndexBuffer& getIndexBuffer() const;
		void setIndexBuffer(IndexBuffer* index_buffer);

		BufferLayout getBufferLayout() const;
		void setBufferLayout(const BufferLayout& buffer_layout);

	private:

		uint32_t m_id;

		std::vector<VertexBuffer*> m_vertex_buffers;

		IndexBuffer* m_index_buffer;

		BufferLayout m_buffer_layout;
	};




	template<typename T>
	void BufferLayout::addAttribute(const uint32_t& vertex_dim)
	{
		assert(false);
	}

	template <>
	inline void BufferLayout::addAttribute<float>(const uint32_t& vertex_dim)
	{
		_addAttribute(vertex_dim, GL_FLOAT);
	}

	template <>
	inline void BufferLayout::addAttribute<uint32_t>(const uint32_t& vertex_dim)
	{
		_addAttribute(vertex_dim, GL_UNSIGNED_INT);
	}

}


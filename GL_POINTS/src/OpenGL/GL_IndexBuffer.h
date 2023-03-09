#pragma once
#include <vector>
#include <cstdint>

#include "GL_DrawTypeEnum.h"


namespace OpenGL
{
	class IndexBuffer
	{
	public:

		IndexBuffer();
		IndexBuffer(uint32_t* indices, const uint32_t& count);
		~IndexBuffer();

		IndexBuffer(const IndexBuffer& obj) = delete;
		IndexBuffer& operator=(const IndexBuffer& obj) = delete;

		IndexBuffer(IndexBuffer&& obj) = delete;
		IndexBuffer& operator=(IndexBuffer&& obj) = delete;

		void create(uint32_t* indices, const uint32_t& count);

		void bind() const;

		uint32_t getIndiceCount() const;

	private:

		uint32_t m_id;

		uint32_t m_indice_count;
	};
}




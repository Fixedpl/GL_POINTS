#pragma once
#include <cstdint>
#include <string>



namespace OpenGL {

	class ComputeShader
	{
	public:

		ComputeShader();
		ComputeShader(const std::string& path);
		~ComputeShader();

		ComputeShader(const ComputeShader& obj) = delete;
		ComputeShader& operator=(const ComputeShader& obj) = delete;

		ComputeShader(ComputeShader&& obj) = delete;
		ComputeShader& operator=(ComputeShader&& obj) = delete;

		void bind() const;

		void loadShader(const std::string& path);

	private:

		uint32_t createShader(const std::string& path, const int32_t& type);

	private:

		uint32_t m_id;

	};

}




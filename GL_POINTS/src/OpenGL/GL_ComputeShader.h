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

		void setUniform1i(const std::string& name, const int32_t& value);

	private:

		uint32_t createShader(const std::string& path, const int32_t& type);

		int32_t getUniformLocation(const std::string& name);

	private:

		uint32_t m_id;

	};

}




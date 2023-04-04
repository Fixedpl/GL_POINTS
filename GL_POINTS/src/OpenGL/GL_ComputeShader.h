#pragma once
#include <cstdint>
#include <string>

#include <glm/glm.hpp>


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

		void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
		void setUniform1i(const std::string& name, const int32_t& value);
		void setUniform1ui(const std::string& name, const uint32_t& value);
		void setUniform2i(const std::string& name, const glm::vec2& value);

	private:

		uint32_t createShader(const std::string& path, const int32_t& type);

		int32_t getUniformLocation(const std::string& name);

	private:

		uint32_t m_id;

	};

}




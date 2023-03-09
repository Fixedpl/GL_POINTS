#pragma once
#include <string>
#include <cstdint>

#include <glm/glm.hpp>

namespace OpenGL
{
	class Shader
	{
	public:

		Shader();
		Shader(const std::string& vsPath, const std::string& fsPath);
		~Shader();

		Shader(const Shader& obj) = delete;
		Shader& operator=(const Shader& obj) = delete;

		Shader(Shader&& obj) = delete;
		Shader& operator=(Shader&& obj) = delete;

		void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
		void setUniform1i(const std::string& name, const int32_t& value);
		void setUniform1f(const std::string& name, const float& value);

		void bind() const;

		void loadShader(const std::string& vsPath, const std::string& fsPath);

	private:

		uint32_t createShader(const std::string& path, const int32_t& type);

		int32_t getUniformLocation(const std::string& name);

	private:

		uint32_t m_id;

	};
}



#pragma once
#include <string>
namespace Engine
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;//debug

	private:
		uint32_t m_RendererID;//value that identifys object in OpenGl
	};
}
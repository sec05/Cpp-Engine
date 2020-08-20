#pragma once
namespace ES
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;//debug
		
		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}
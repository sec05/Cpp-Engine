#include "espch.h"
#include "Shader.h"
#include "Renderer.h"
#include "ES/Platform/OpenGL/OpenGLShader.h"
namespace ES
{
	Shader* Shader::Create(const std::string& filepath)
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: ES_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
		}
		ES_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: ES_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc,fragmentSrc);
		}
		ES_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}


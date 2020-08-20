#include "espch.h"
#include "Texture.h"
#include "Renderer.h"
#include "ES/Platform/OpenGL/OpenGLTexture.h"
namespace ES
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: ES_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}
		ES_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
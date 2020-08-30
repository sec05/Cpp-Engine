#include "espch.h"
#include "Texture.h"
#include "Renderer.h"
#include "ES/Platform/OpenGL/OpenGLTexture.h"
namespace ES
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: ES_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width,height);
		}
		ES_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: ES_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}
		ES_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
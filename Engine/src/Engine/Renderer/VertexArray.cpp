#include "espch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Engine/Platform/OpenGL/OpenGLVertexArray.h"
namespace Engine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: ES_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		ES_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}


#include "espch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "ES/Platform/OpenGL/OpenGLVertexArray.h"
namespace ES
{
	Ref<VertexArray> VertexArray::Create()
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: ES_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}
		ES_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}


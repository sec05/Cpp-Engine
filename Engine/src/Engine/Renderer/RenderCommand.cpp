#include "espch.h"
#include "RenderCommand.h"
#include "Engine/Platform/OpenGL/OpenGLRendererAPI.h"
namespace Engine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;//technically a 1byte memory leak
}
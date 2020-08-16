#include "espch.h"
#include "RenderCommand.h"
#include "ES/Platform/OpenGL/OpenGLRendererAPI.h"
namespace ES
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;//technically a 1byte memory leak
}
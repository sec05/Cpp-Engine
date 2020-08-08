#pragma once
#include "RenderCommand.h"
namespace Engine
{

	class Renderer
	{
	public:
		static void BeginScene(); //needs to take in scene parameters
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		
	};

	
}
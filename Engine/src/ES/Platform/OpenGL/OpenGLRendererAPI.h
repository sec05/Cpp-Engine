#pragma once
#include "ES/Renderer/RendererAPI.h"
namespace ES
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}



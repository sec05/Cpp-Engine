#pragma once
#include "OrthographicCamera.h"
namespace ES
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();


		//primatives
		static void DrawQaud(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQaud(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	};
}



#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"
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
		static void DrawTriangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const float& rotation = 0.0f);
		static void DrawTriangle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const float& rotation = 0.0f);
		static void DrawQaud(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color,const float& rotation = 0.0f);
		static void DrawQaud(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color,const float& rotation = 0.0f);
		static void DrawQaud(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& rotation = 0.0f);
		static void DrawQaud(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& rotation = 0.0f);
	};
}



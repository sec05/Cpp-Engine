#include "espch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>
namespace ES
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> TriVertexArray;
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
		Ref<Shader> TextureShader;
		
	};
	static Renderer2DStorage* s_Data;
	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();
		s_Data->TriVertexArray = VertexArray::Create();

		float SQvertices[5 * 4] = {//screen right now is -1 to 1 because there is no projection matrix
			-0.5f, -0.5f, 0.0f,0.0f,0.0f,	//bottom left of square is 0,0 top right is 1,1 for tex coords
			 0.5f, -0.5f, 0.0f,1.0f,0.0f,
			 0.5f,  0.5f, 0.0f,1.0f,1.0f,
			-0.5f,  0.5f, 0.0f,0.0f,1.0f,

		};
		Ref<VertexBuffer> SquareVB;
		SquareVB.reset(ES::VertexBuffer::Create(SQvertices, sizeof(SQvertices)));
		SquareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_Texture"}

			});
		s_Data->QuadVertexArray->AddVertexBuffer(SquareVB);
		uint32_t squareIndicies[6] = { 0,1,2,2,3,0 };//draws 2 triangles so 0,1,2 then 2,3,0 for the different points
		Ref<IndexBuffer> SquareIB;
		SquareIB.reset(IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(SquareIB);

		float TriVertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,

		};
		Ref<VertexBuffer> TriangleVB;
		TriangleVB.reset(ES::VertexBuffer::Create(TriVertices, sizeof(TriVertices)));
		TriangleVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
			});
		s_Data->TriVertexArray->AddVertexBuffer(TriangleVB);
		uint32_t triangleIndicies[3] = { 0,1,2 };
		Ref<IndexBuffer> TriangleIB;
		TriangleIB.reset(IndexBuffer::Create(triangleIndicies, sizeof(triangleIndicies) / sizeof(uint32_t)));
		s_Data->TriVertexArray->SetIndexBuffer(TriangleIB);
		
		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColorShader.glsl");
		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->SetInt("u_Texture", 0);//samples from texture slot 0
	}
	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

	
	}
	void Renderer2D::EndScene()
	{
	}
	void Renderer2D::DrawTriangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const float& rotation)
	{
		DrawTriangle({ position.x,position.y,0.0f }, size, color, rotation);
	}
	void Renderer2D::DrawTriangle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const float& rotation)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		s_Data->FlatColorShader->SetMat4("u_Transform", transform);
		s_Data->TriVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->TriVertexArray);
	}
	void Renderer2D::DrawQaud(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const float& rotation)
	{
		DrawQaud({ position.x,position.y, 0.0f }, size, color,rotation);
	}
	void Renderer2D::DrawQaud(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const float& rotation)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *glm::rotate(glm::mat4(1.0f),glm::radians(rotation),glm::vec3(0,0,1))* glm::scale(glm::mat4(1.0f), {size.x,size.y,1.0f});
		s_Data->FlatColorShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
	void Renderer2D::DrawQaud(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& rotation)
	{
		DrawQaud({ position.x,position.y,0.0f }, size, texture, rotation);
	}
	void Renderer2D::DrawQaud(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& rotation)
	{
		s_Data->TextureShader->Bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		texture->Bind();
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}
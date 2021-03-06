#include "Engine.h"
#include <ES/Core/EntryPoint.h>
#include "imgui/imgui.h"
#include "ES/Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"
class ExampleLayer : public ES::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f/720.0f, true), m_CameraPosition(0.0f)
	{
		m_VertexArray = (ES::VertexArray::Create());
		float vertices[3 * 7] = {//screen right now is -1 to 1 because there is no projection matrix
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.9f, 0.4f, 0.1f, 1.0f

		};
		m_VertexBuffer.reset(ES::VertexBuffer::Create(vertices, sizeof(vertices)));
		ES::BufferLayout layout = {
			{ES::ShaderDataType::Float3, "a_Position"},
			{ES::ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indicies[3] = { 0,1,2, };
		m_IndexBuffer.reset(ES::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_SquareVA = (ES::VertexArray::Create());
		float SQvertices[5 * 4] = {//screen right now is -1 to 1 because there is no projection matrix
			-0.5f, -0.5f, 0.0f,0.0f,0.0f,//bottom left of square is 0,0 top right is 1,1 for tex coords
			 0.5f, -0.5f, 0.0f, 1.0f,0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f,1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f,1.0f,

		};
		ES::Ref<ES::VertexBuffer> SquareVB;
		SquareVB.reset(ES::VertexBuffer::Create(SQvertices, sizeof(SQvertices)));
		SquareVB->SetLayout({
			{ES::ShaderDataType::Float3, "a_Position"},
			{ES::ShaderDataType::Float2, "a_TexCoord"},
			});
		m_SquareVA->AddVertexBuffer(SquareVB);
		uint32_t squareIndicies[6] = { 0,1,2,2,3,0 };//draws 2 triangles so 0,1,2 then 2,3,0 for the different points
		ES::Ref<ES::IndexBuffer> SquareIB;
		SquareIB.reset(ES::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(SquareIB);
		
	
		m_FlatColorShader = ES::Shader::Create("assets/shaders/FlatColorShader.glsl");

	
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = ES::Texture2D::Create("assets/textures/woody.png");
		m_AlphaTexture = ES::Texture2D::Create("assets/textures/butterfly.png");
		std::dynamic_pointer_cast<ES::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<ES::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}
	
	void OnUpdate(ES::Timestep ts) override//happens every frame
	{
		//ES_TRACE("Delta Time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		fps = 1.0f / ts;
		
		m_CameraController.OnUpdate(ts);
		
		ES::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ES::RenderCommand::Clear();
		ES::Renderer::BeginScene(m_CameraController.GetCamera());
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<ES::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<ES::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_FlatColor);
		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		ES::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		glm::mat4 butterflyTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f,0.0f,0.0f));
		m_AlphaTexture->Bind();
		ES::Renderer::Submit(textureShader, m_SquareVA, butterflyTransform);
		
		glm::mat4 triangleTransform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f));
		ES::Renderer::Submit(m_FlatColorShader, m_VertexArray, triangleTransform);
		ES::Renderer::EndScene();
	}
	void OnEvent(ES::Event& e) override//events happen once 
	{
		 
		m_CameraController.OnEvent(e);
		ES::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<ES::MouseMovedEvent>(ES_BIND_EVENT_FN(ExampleLayer::MouseMoved));
		
			
	}
	bool MouseMoved(ES::Event& e) 
	{
		ES::MouseMovedEvent mm = (ES::MouseMovedEvent&)e;
		//ES_TRACE("{0},{1}", mm.GetX(), mm.GetY());
		return false;
	}
	virtual void OnImGuiRender() override//gets called in application.cpp
	{
		ImGui::Begin("System Information");
		ImGui::Text("FPS: %f", floor(fps));
		ImGui::Text("Vendor: %s", m_SystemInfo.GetVendor());
		ImGui::Text("Renderer: %s", m_SystemInfo.GetRenderer());
		ImGui::Text("Version: %s", m_SystemInfo.GetVersion());
		ImGui::End();

		ImGui::Begin("Flat Color Shader");
		ImGui::ColorPicker3("Flat Color Shader Picker",glm::value_ptr(m_FlatColor));
		ImGui::End();
	}
private:
	ES::ShaderLibrary m_ShaderLibrary;
	ES::Ref<ES::Shader> m_Shader;
	ES::Ref<ES::Shader> m_FlatColorShader;
	ES::Ref<ES::VertexArray> m_VertexArray;
	ES::Ref<ES::VertexBuffer> m_VertexBuffer;
	ES::Ref<ES::IndexBuffer> m_IndexBuffer;
	ES::Ref<ES::VertexArray> m_SquareVA;
	ES::Ref<ES::Texture2D> m_Texture, m_AlphaTexture;
	ES::OrthographicCameraController m_CameraController;
	ES::SystemInformation m_SystemInfo;
	glm::vec3 m_CameraPosition;
	glm::vec3 m_FlatColor = { 0.2f,0.5f,0.8f };
	float m_CameraRotation;
	float fps;

	glm::vec3 m_SquarePosition;
};


class Sandbox : public ES::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}
};
ES::Application* ES::CreateApplication() {
	return new Sandbox;
}
#include "Engine.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ES/Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
class ExampleLayer : public ES::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f),m_CameraRotation(0.0f),m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(ES::VertexArray::Create());
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
		m_SquareVA.reset(ES::VertexArray::Create());
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
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location =1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position=u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			} 
			


			)";
		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;	
			in vec4 v_Color;	
			void main()
			{
				
				color = vec4(v_Position*2+0.75,1.0);
				color = v_Color;
			} 
			


			)";

		m_Shader.reset(ES::Shader::Create(vertexSrc, fragmentSrc));
		std::string FlatColorVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position=u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			} 
			


			)";
		std::string FlatColorFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;	
			uniform vec3 u_Color;
			void main()
			{
				
				color = vec4(u_Color,1.0);
			} 
			


			)";
		m_FlatColorShader.reset(ES::Shader::Create(FlatColorVertexSrc, FlatColorFragmentSrc));

		std::string textureShaderVertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoords;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec2 v_TexCoords;
			void main()
			{
				v_TexCoords = a_TexCoords;
				gl_Position=u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			} 
			


			)";
		std::string textureShaderFragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec2 v_TexCoords;
			uniform sampler2D u_Texture;
			void main()
			{
				
				color = texture(u_Texture,v_TexCoords);
			} 
			


			)";
		m_TextureShader.reset(ES::Shader::Create(textureShaderVertexSrc2, textureShaderFragmentSrc2));
		m_Texture = ES::Texture2D::Create("assets/textures/woody.png");
		m_AlphaTexture = ES::Texture2D::Create("assets/textures/butterfly.png");
		std::dynamic_pointer_cast<ES::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<ES::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}
	
	void OnUpdate(ES::Timestep ts) override//happens every frame
	{
		//ES_TRACE("Delta Time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		fps = 1.0f / ts;
		
		if (ES::Input::IsKeyPressed(ES_KEY_W))
		{
			m_CameraPosition.y += 1.0f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_A))
		{
			m_CameraPosition.x -= 1.0f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_S))
		{
			m_CameraPosition.y -= 1.0f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_D))
		{
			m_CameraPosition.x += 1.0f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_R))
		{
			m_CameraPosition.x = 0.0f;
			m_CameraPosition.y = 0.0f;
			m_CameraPosition.z = 0.0f;
			m_CameraRotation = 0.0f;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_UP))
		{
			m_SquarePosition.y += 1.0f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_LEFT))
		{
			m_SquarePosition.x -= 1.0f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_DOWN))
		{
			m_SquarePosition.y -= 1.0f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_RIGHT))
		{
			m_SquarePosition.x += 1.0f * ts;
		}
		ES::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ES::RenderCommand::Clear();
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		ES::Renderer::BeginScene(m_Camera);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<ES::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<ES::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color",m_SquareColor);
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
					{
						glm::vec3 pos(x * 0.11f, y*0.11f, 0.0f);
						glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
						
					
							
					}
		}
		m_Texture->Bind();
		ES::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_AlphaTexture->Bind();
		ES::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
			//triangle
		//ES::Renderer::Submit(m_Shader, m_VertexArray);
		ES::Renderer::EndScene();
	}
	void OnEvent(ES::Event& e) override//events happen once 
	{
		ES::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<ES::MouseScrolledEvent>(ES_BIND_EVENT_FN(ExampleLayer::OnMouseScroll));


	}
	bool OnMouseScroll(ES::Event& e)
	{

		ES::MouseScrolledEvent& kp = (ES::MouseScrolledEvent&)e;
		m_CameraRotation += kp.GetYOffset() * 4;
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
	}
private:
	ES::Ref<ES::Shader> m_Shader;
	ES::Ref<ES::Shader> m_FlatColorShader, m_TextureShader;
	ES::Ref<ES::VertexArray> m_VertexArray;
	ES::Ref<ES::VertexBuffer> m_VertexBuffer;
	ES::Ref<ES::IndexBuffer> m_IndexBuffer;
	ES::Ref<ES::VertexArray> m_SquareVA;
	ES::Ref<ES::Texture2D> m_Texture, m_AlphaTexture;
	ES::OrthographicCamera m_Camera;
	ES::SystemInformation m_SystemInfo;
	glm::vec3 m_CameraPosition;
	glm::vec3 m_SquareColor = { 0.2f,0.5f,0.8f };
	float m_CameraRotation;
	float fps;

	glm::vec3 m_SquarePosition;
};


class Sandbox : public ES::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		
	}
	~Sandbox()
	{

	}
};
ES::Application* ES::CreateApplication() {
	return new Sandbox;
}
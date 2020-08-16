#include "Engine.h"
#include "imgui/imgui.h"

class ExampleLayer : public ES::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f),m_CameraRotation(0.0f)
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
		float SQvertices[3 * 4] = {//screen right now is -1 to 1 because there is no projection matrix
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f

		};
		std::shared_ptr<ES::VertexBuffer> SquareVB;
		SquareVB.reset(ES::VertexBuffer::Create(SQvertices, sizeof(SQvertices)));
		SquareVB->SetLayout({
			{ES::ShaderDataType::Float3, "a_Position"},
			});
		m_SquareVA->AddVertexBuffer(SquareVB);
		uint32_t squareIndicies[6] = { 0,1,2,2,3,0 };//draws 2 triangles so 0,1,2 then 2,3,0 for the different points
		std::shared_ptr<ES::IndexBuffer> SquareIB;
		SquareIB.reset(ES::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(SquareIB);
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location =1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position=u_ViewProjection * vec4(a_Position,1.0);
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

		m_Shader.reset(new ES::Shader(vertexSrc, fragmentSrc));
		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position=u_ViewProjection*vec4(a_Position,1.0);
			} 
			


			)";
		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;	
			void main()
			{
				
				color = vec4(0.2,0.3,1.0,1.0);
			} 
			


			)";
		m_blueShader.reset(new ES::Shader(vertexSrc2, fragmentSrc2));
	}
	
	void OnUpdate(ES::Timestep ts) override//happens every frame
	{
		//ES_TRACE("Delta Time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		fps = 1.0f / ts;
		if (ES::Input::IsKeyPressed(ES_KEY_W))
		{
			m_CameraPosition.y += 0.25f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_A))
		{
			m_CameraPosition.x -= 0.25f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_S))
		{
			m_CameraPosition.y -= 0.25f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_D))
		{
			m_CameraPosition.x += 0.25f * ts;
		}
		if (ES::Input::IsKeyPressed(ES_KEY_R))
		{
			m_CameraPosition.x = 0.0f;
			m_CameraPosition.y = 0.0f;
			m_CameraPosition.z = 0.0f;
			m_CameraRotation = 0.0f;
		}
	
		ES::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ES::RenderCommand::Clear();
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		ES::Renderer::BeginScene(m_Camera);
		ES::Renderer::Submit(m_blueShader, m_SquareVA);
		ES::Renderer::Submit(m_Shader, m_VertexArray);
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
		ImGui::Begin("FPS");
		ImGui::Text("FPS: %f" , floor(fps));
		ImGui::End();
	}
private:
	std::shared_ptr<ES::Shader> m_Shader;
	std::shared_ptr<ES::Shader> m_blueShader;
	std::shared_ptr<ES::VertexArray> m_VertexArray;
	std::shared_ptr<ES::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<ES::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<ES::VertexArray> m_SquareVA;
	ES::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_CameraRotation;
	float fps;
};


class SandBox : public ES::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		
	}
	~SandBox()
	{

	}
};
ES::Application* ES::CreateApplication() {
	return new SandBox;
}
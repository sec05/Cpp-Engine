#include "espch.h"
#include "Application.h"
#include <glad/glad.h>
#include <random>
#include "Input.h"
#include "Engine/Renderer/Renderer.h"
#include "KeyCodes.h"
namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x,this, std::placeholders::_1)//this event and the event name


	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Engine::ShaderDataType::Float:  return GL_FLOAT;
			case Engine::ShaderDataType::Float2: return GL_FLOAT;
			case Engine::ShaderDataType::Float3: return GL_FLOAT;
			case Engine::ShaderDataType::Float4: return GL_FLOAT;
			case Engine::ShaderDataType::Mat3:	 return GL_FLOAT;	
			case Engine::ShaderDataType::Mat4:	 return GL_FLOAT;
			case Engine::ShaderDataType::Int:	 return GL_INT;
			case Engine::ShaderDataType::Int2:	 return GL_INT;
			case Engine::ShaderDataType::Int3:	 return GL_INT;
			case Engine::ShaderDataType::Int4:	 return GL_INT;
			case Engine::ShaderDataType::Bool:	 return GL_BOOL;
		}
		ES_CORE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}

	Application::Application()
		:m_Camera(-1.6,1.6f,-0.9f, 0.9f)
	{
		ES_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		//m_Window->SetVSync(false);
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());
		float vertices[3 * 7] = {//screen right now is -1 to 1 because there is no projection matrix
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.9f, 0.4f, 0.1f, 1.0f

		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indicies[3] = { 0,1,2, };
		m_IndexBuffer.reset(IndexBuffer::Create(indicies, sizeof(indicies)/sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_SquareVA.reset(VertexArray::Create());
		float SQvertices[3 * 4] = {//screen right now is -1 to 1 because there is no projection matrix
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f

		};
		std::shared_ptr<VertexBuffer> SquareVB; 
		SquareVB.reset(VertexBuffer::Create(SQvertices, sizeof(SQvertices)));
		SquareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			});
		m_SquareVA->AddVertexBuffer(SquareVB);
		uint32_t squareIndicies[6] = { 0,1,2,2,3,0 };//draws 2 triangles so 0,1,2 then 2,3,0 for the different points
		std::shared_ptr<IndexBuffer> SquareIB;
		SquareIB.reset(IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
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
	
		m_Shader.reset(new Shader(vertexSrc,fragmentSrc));
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
		m_blueShader.reset(new Shader(vertexSrc2, fragmentSrc2));
	}
	Application::~Application()
	{}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	float x;
	float y;
	float z;
	float r = 0.0f;
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);//checks if event is a closed event by checking the static type of the template of the event
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		if (e.GetEventType() == EventType::MouseScrolled)
		{
			MouseScrolledEvent& kp = (MouseScrolledEvent&)e;
			r += kp.GetYOffset();

		}
		if (e.GetEventType() == EventType::KeyPressed)
		{
			KeyPressedEvent& kp = (KeyPressedEvent&)e;
			if (kp.GetKeyCode() == ES_KEY_W)
			{
				y += 0.1;
			}
			if (kp.GetKeyCode() == ES_KEY_A)
			{
				x -= 0.1f;
			}
			if (kp.GetKeyCode() == ES_KEY_S)
			{
				y -= 0.1f;
			}
			if (kp.GetKeyCode() == ES_KEY_D)
			{
				x += 0.1f;
			}
		}
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() {
		

		while (m_Running)
		{

			
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
			m_Camera.SetPosition({ x,y,z});
			m_Camera.SetRotation(r);
			Renderer::BeginScene(m_Camera);
			Renderer::Submit(m_blueShader,m_SquareVA);
			Renderer::Submit(m_Shader,m_VertexArray);
			Renderer::EndScene();
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
				
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
		
			m_Window->OnUpdate();
			
		};
	}
	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
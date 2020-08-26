#include "espch.h"
#include "ES/Core/Application.h"
#include <glad/glad.h>
#include "ES/Core/Log.h"
#include "ES/Renderer/Renderer.h"
#include <GLFW/glfw3.h>
namespace ES {

#define BIND_EVENT_FN(x) std::bind(&Application::x,this, std::placeholders::_1)//this event and the event name


	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ES::ShaderDataType::Float:		return GL_FLOAT;
			case ES::ShaderDataType::Float2:	return GL_FLOAT;
			case ES::ShaderDataType::Float3:	return GL_FLOAT;
			case ES::ShaderDataType::Float4:	return GL_FLOAT;
			case ES::ShaderDataType::Mat3:		return GL_FLOAT;	
			case ES::ShaderDataType::Mat4:		return GL_FLOAT;
			case ES::ShaderDataType::Int:		return GL_INT;
			case ES::ShaderDataType::Int2:		return GL_INT;
			case ES::ShaderDataType::Int3:		return GL_INT;
			case ES::ShaderDataType::Int4:		return GL_INT;
			case ES::ShaderDataType::Bool:		return GL_BOOL;
		}
		ES_CORE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}

	Application::Application()
		
	{
		ES_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());//makes the window
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(false);
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		Renderer::Init();
		
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

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
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
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
			
		};
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		
		return false;
	}
}
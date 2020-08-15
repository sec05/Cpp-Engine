#include "espch.h"
#include "Application.h"
#include <glad/glad.h>
#include "Engine/Log.h"
#include "Engine/Renderer/Renderer.h"

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
		
	{
		ES_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		//m_Window->SetVSync(false);
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		
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

			
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
				
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
}
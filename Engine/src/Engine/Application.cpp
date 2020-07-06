#include "espch.h"
#include "Application.h"
#include <glad/glad.h>
#include <random>
#include "Input.h"
namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x,this, std::placeholders::_1)//this event and the event name

	Application* Application::s_Instance = nullptr;

	double fRand(double fMin, double fMax)
	{
		double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}
	Application::Application()
	{
		ES_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

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
		EventDispatcher dispatcher(e);//checks if event is a closed event by checking the static type of the template of the event
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		ES_CORE_TRACE("{0}",e);

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
				m_Window->OnUpdate();

				auto [x, y] = Input::GetMousePosition();
				if (x >= 500)
				{
					ES_CORE_TRACE("{0},{1}", x, y);
				}
		};
	}
	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
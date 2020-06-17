#include "espch.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include <random>
namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x,this, std::placeholders::_1)//this event and the event name
	double fRand(double fMin, double fMax)
	{
		double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	Application::~Application()
	{}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);//checks if event is a closed event by checking the static type of the template of the event
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		ES_CORE_TRACE("{0}",e);
	}

	void Application::Run() {
		

		while (m_Running)
		{
			glClearColor(fRand(0,1), fRand(0, 1), fRand(0, 1), 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		};
	}
	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
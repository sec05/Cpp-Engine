#include "Application.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Log.h"
namespace Engine {
	Application::Application()
	{}
	Application::~Application()
	{}
	void Application::Run() {
		WindowResizeEvent e(2000, 720);
		ES_TRACE(e);
		MouseButtonPressedEvent t(2);
		ES_TRACE(t);
		KeyPressedEvent f(3,0);
		ES_TRACE(f);

		while (true)
		{

		};
	}
}
#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace Engine {
	class ES_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};
	Application* CreateApplication();//defined in client
}

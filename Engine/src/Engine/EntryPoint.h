#pragma once
#ifdef ES_PLATFORM_WINDOWS
extern Engine::Application* Engine::CreateApplication();
void main(int argc, char** argv) {
	Engine::Log::Init();
	ES_CORE_WARN("Initialized the CORE log!");
	ES_INFO("Initialized the APP log!");
	auto app = Engine::CreateApplication();
	app->Run();//runs an infinite window that is allocated on the heap
	delete app;

}
#endif 

#pragma once
#ifdef ES_PLATFORM_WINDOWS
extern ES::Application* ES::CreateApplication();
void main(int argc, char** argv) {
	ES::Log::Init();
	ES_CORE_WARN("Initialized the CORE log!");
	ES_INFO("Initialized the APP log!");
	auto app = ES::CreateApplication();
	app->Run();//runs an infinite window that is allocated on the heap
	delete app;

}
#endif 

#pragma once
#ifdef ES_PLATFORM_WINDOWS
extern ES::Application* ES::CreateApplication();
void main(int argc, char** argv) {
	ES::Log::Init();
	ES_PROFILE_BEGIN_SESSION("Startup", "ESProfile-Startup.json");
	auto app = ES::CreateApplication();
	ES_PROFILE_END_SESSION();

	ES_PROFILE_BEGIN_SESSION("Runtime", "ESProfile-Runtime.json");
	app->Run();//runs an infinite window that is allocated on the heap
	ES_PROFILE_END_SESSION();

	ES_PROFILE_BEGIN_SESSION("Shutdown", "ESProfile-Shutdown.json");
	delete app;
	ES_PROFILE_END_SESSION();

}
#endif 

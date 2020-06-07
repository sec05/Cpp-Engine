#pragma once
#ifdef ES_PLATFORM_WINDOWS
extern Engine::Application* Engine::CreateApplication();
void main(int argc, char** argv) {
	Engine::Log::Init();
	ES_CORE_WARN("Initialized the log!");
	ES_INFO("Initialized the log!");
	int a = 5;
	ES_INFO("Hi! Var={0}", a);
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;

}
#endif // ES_PLATFORM_WINDOWS

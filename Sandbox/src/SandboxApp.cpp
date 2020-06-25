#include "Engine.h"
class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		ES_INFO("ExampleLayer::Update");
	}
	void OnEvent(Engine::Event& event) override
	{
		ES_TRACE("{0}", event);
	}
};


class SandBox : public Engine::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Engine::ImGuiLayer());
	}
	~SandBox()
	{

	}
};
Engine::Application* Engine::CreateApplication() {
	return new SandBox;
}
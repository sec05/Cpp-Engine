#include "Engine.h"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override//happens every frame
	{
		if (Engine::Input::IsKeyPressed(ES_KEY_TAB))
		{
			ES_TRACE("Tab Key Pressed poll");
		}
		if (Engine::Input::IsMouseButtonPressed(ES_MOUSE_BUTTON_5))
			ES_TRACE("Mouse Button 5 was pressed");
	}
	void OnEvent(Engine::Event& event) override//events happen once 
	{
		if (event.GetEventType() ==Engine::EventType::KeyPressed)
		{
			Engine::KeyPressedEvent& e = (Engine::KeyPressedEvent&)event;
			ES_TRACE("{0}", (char)e.GetKeyCode());
			if (e.GetKeyCode() == ES_KEY_TAB)
				ES_TRACE("Tab was pressed event");
		}
		//ES_TRACE("{0}", event);
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
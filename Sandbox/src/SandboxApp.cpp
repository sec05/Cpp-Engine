#include "Engine.h"
#include "imgui/imgui.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}
class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		auto cam = camera(0.f, { 0.1f,0.8f });

	}

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
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("test");
		ImGui::Text("Hellow World");
		ImGui::End();
	}
};


class SandBox : public Engine::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		
	}
	~SandBox()
	{

	}
};
Engine::Application* Engine::CreateApplication() {
	return new SandBox;
}
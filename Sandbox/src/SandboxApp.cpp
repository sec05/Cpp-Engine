#include "Engine.h"
#include "imgui/imgui.h"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

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
	virtual void OnImGuiRender() override//gets called in application.cpp
	{
		/*static bool my_tool_active = true;
		static float my_color = 0.99f;
		ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ //}
		/*		if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */// }
		/*		if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// Edit a color (stored as ~4 floats)
		ImGui::ColorEdit4("Color", &my_color);

		// Plot some values
		const float my_values[] = { 0.2f, 56.0f, 1.0f, 0.5f, 0.9f, 2.2f ,0.0f,100.9f};
		ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

		// Display contents in a scrolling region
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
		ImGui::BeginChild("Scrolling");
		for (int n = 0; n < 50; n++)
			ImGui::Text("%04d: Some text", n);
		ImGui::EndChild();
		ImGui::End();*/

		
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
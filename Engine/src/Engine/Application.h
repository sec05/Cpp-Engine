#pragma once
#include "Core.h"
#include "Engine/Events/Event.h"
#include "Window.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/LayerStack.h"

#include "Engine/ImGui/ImGuiLayer.h"
namespace Engine {
	class   Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline  static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	private:
		static Application* s_Instance;
	};
	Application* CreateApplication();//defined in client
}

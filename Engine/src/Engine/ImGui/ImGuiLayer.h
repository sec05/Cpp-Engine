#pragma once
#include "Engine/Layer.h"

#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/ApplicationEvent.h"
namespace Engine
{
	class   ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;//where we draw stuff
		
		void Begin();//we want layers to be able to render there own imgui controls
		void End();
	private:
		float m_Time = 0.0f;
	};
}
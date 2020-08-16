#pragma once
#include "ES/Layer.h"

#include "ES/Events/KeyEvent.h"
#include "ES/Events/MouseEvent.h"
#include "ES/Events/ApplicationEvent.h"
namespace ES
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
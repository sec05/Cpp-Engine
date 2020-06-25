#pragma once

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace Engine
{
	class ES_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}//pushed on layer stack
		virtual void OnDetach() {}
		virtual void OnUpdate() {}//every frame
		virtual void OnEvent(Event& event){}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}

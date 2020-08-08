#include "espch.h"
#include "LayerStack.h"

namespace Engine
{
	LayerStack::LayerStack()
	{
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}


	void LayerStack::PushLayer(Layer* layer)//first half of the list
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)//second half of thelist
	{
		m_Layers.emplace_back(overlay);
	}


	void LayerStack::PopLayer(Layer* layer)//dont lose layers until dystroyed just removes from vector
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);

		}
	}
}
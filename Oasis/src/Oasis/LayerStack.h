#pragma once

#include "OApch.h"
#include "Core.h"
#include "Layer.h"
#include "Events/Event.h"

namespace Oasis {

	class OASIS_API LayerStack
	{

	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:

		std::vector<Layer*> m_Layers;
		unsigned int m_LayerIndex = 0;

	};

}


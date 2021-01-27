#pragma once

#include "Almond/Core.h"
#include "Almond/Core/Timestep.h"
#include "Almond/Events/Event.h"

namespace Almond {

	class ALMOND_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach(){}
		virtual void onUpdate(Timestep ts) {}
		virtual void onImGuiRender(float fr) {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
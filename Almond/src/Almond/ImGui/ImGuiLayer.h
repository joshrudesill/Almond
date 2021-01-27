#pragma once

#include "Almond/Layer.h"
#include "Almond/Events/KeyEvent.h"
#include "Almond/Events/MouseEvent.h"
#include "Almond/Events/ApplicationEvent.h"

namespace Almond {
	
	class ALMOND_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender(float fr) override;
		void begin();
		void end();
		
	private:
		float m_Time = 0.0f; 
	
	};
}
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
		virtual void onAttach();
		virtual void onDetach();
		void onUpdate();
		void onEvent(Event& event);
	private:
		float m_Time = 0.0f; 
	private:
		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool onMouseMovedEvent(MouseMovedEvent& e);
		bool onMouseScrolledEvent(MouseScrolledEvent& e);
		bool onKeyPressedEvent(KeyPressedEvent& e);
		bool onKeyReleasedEvent(KeyReleasedEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);
		bool onKeyTypedEvent(KeyTypedEvent& e);
	};
}
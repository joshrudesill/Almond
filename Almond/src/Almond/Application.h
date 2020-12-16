#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Almond/LayerStack.h"
#include "Window.h"
#include "Almond/Events/ApplicationEvent.h"

namespace Almond {

	class ALMOND_API Application
	{
	public:
		Application();

		virtual ~Application();
		void run();
		void onEvent(Event& e);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		inline static Application& get() { return *s_Instance; }
		inline Window& getWindow() { return *m_Window; }

	private:
		bool onWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	Application* createApplication();
}



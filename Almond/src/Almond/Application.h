#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Almond/LayerStack.h"
#include "Window.h"
#include "Almond/Events/ApplicationEvent.h"
#include "Almond/ImGui/ImGuiLayer.h"

#include "Almond/Renderer/Shader.h"
#include "Almond/Renderer/Buffer.h"
#include "Almond/Renderer/VertexArray.h"

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
		inline Window& getWindow() { return *m_Window; }
		inline static Application& get() { return *s_Instance; }
		

	private:
		bool onWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		
		std::shared_ptr<Shader> m_Shader;
	
		std::shared_ptr<VertexArray> m_VertexArray;



	private:
		static Application* s_Instance;
	};

	Application* createApplication();
}



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
#include "Almond/Renderer/OrthographicCamera.h"
#include "Almond/Core/Timestep.h"

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
		
		void updateFrameCount(Timestep ts) {
			frameTotal += ts.getSeconds();
			frames++;

			if (frames % 1000 == 0) {
				frames = 0;
				frameTotal = 0.0f;
			}
				
		
			
			AvgFrameRate = 1.0f / (frameTotal / frames);
		}

	private:
		bool onWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastTime = 0.0f;
		int frames = 0;
		float frameTotal = 0.0f;
		float AvgFrameRate = 0.0f;


	private:
		static Application* s_Instance;
	};

	Application* createApplication();
}



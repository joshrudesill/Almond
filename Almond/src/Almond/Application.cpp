#include "hzpch.h"
#include "Application.h"
#include "Almond/Renderer/Renderer.h"
#include "Almond/Log.h"
#include "Input.h"
#include "glm/glm.hpp"
#include <GLFW/glfw3.h>

namespace Almond {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	
	Application::Application()
	{
		AL_CORE_ASSERT(!s_Instance, "Application already exists.");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->setEventCallback(BIND_EVENT_FN(onEvent));

		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);
		AL_INFO("VSync: {0}", m_Window->isVSync());
		
		
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->onEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	Application::~Application()
	{
	}

	void Application::pushLayer(Layer* layer)
	{
		m_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_LayerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	void Application::run()
	{
		
		while (m_Running) {

			float time = (float)glfwGetTime();

			Timestep timestep = time - m_LastTime;

			updateFrameCount(timestep);

			m_LastTime = time;

			for (Layer* layer : m_LayerStack)
				layer->onUpdate(timestep);

			m_ImGuiLayer->begin();

			for (Layer* layer : m_LayerStack)
				layer->onImGuiRender(AvgFrameRate);
			m_ImGuiLayer->end();

			auto [x, y] = Input::getMousePosition();

			
			m_Window->onUpdate();
		}
	}
}

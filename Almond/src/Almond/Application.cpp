#include "hzpch.h"
#include "Application.h"

#include "Almond/Log.h"
#include "glad/glad.h"
#include "Input.h"
#include "glm/glm.hpp"


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
		
		m_VertexArray.reset(VertexArray::create());


		float vertices[] = {
			  0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
			 -0.2f, 0.8f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			  0.2f, 0.8f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
		};

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));


		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->setLayout(layout);

		m_VertexArray->addVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };

		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->setIndexBuffer(m_IndexBuffer);

		//----

		m_SquareVA.reset(VertexArray::create());
		
		float Svertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> sqaredVB;
		sqaredVB.reset(VertexBuffer::create(Svertices, sizeof(Svertices)));
		sqaredVB->setLayout( {
			{ShaderDataType::Float3, "a_Position"},
		});
		

		m_SquareVA->addVertexBuffer(sqaredVB);
		uint32_t Sindices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> sqaredIB;
		sqaredIB.reset(IndexBuffer::create(Sindices, sizeof(Sindices) / sizeof(uint32_t)));

		m_SquareVA->setIndexBuffer(sqaredIB);

		//----------

		std::string vertexSrc = R"(
			#version 330 core
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			layout(location=0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));


		std::string vertexSrc2 = R"(
			#version 330 core
			layout(location=0) in vec3 a_Position;
			

			out vec3 v_Position;
			

			void main()
			{
				v_Position = a_Position;
			
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc2 = R"(
			#version 330 core
			layout(location=0) out vec4 color;
			in vec3 v_Position;
		
			void main()
			{
				color = vec4(1.0,1.0,0.0,1.0);
				
			}
		)";

		m_Shader2.reset(new Shader(vertexSrc2, fragmentSrc2));
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
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_SquareVA->bind();
			m_Shader2->bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->getIndexBuffers()->getCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->bind();
			m_VertexArray->bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->getIndexBuffers()->getCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->onUpdate();

			m_ImGuiLayer->begin();
			for (Layer* layer : m_LayerStack)
				layer->onImGuiRender();
			m_ImGuiLayer->end();

			auto [x, y] = Input::getMousePosition();

			
			m_Window->onUpdate();
		}
	}
}

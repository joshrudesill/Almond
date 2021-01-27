#include <Almond.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Almond::Layer 
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f ), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Almond::VertexArray::create());


		float vertices[] = {
			  0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
			 -0.2f, 0.8f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			  0.2f, 0.8f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
		};

		Almond::Ref<Almond::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Almond::VertexBuffer::create(vertices, sizeof(vertices)));


		Almond::BufferLayout layout = {
			{Almond::ShaderDataType::Float3, "a_Position"},
			{Almond::ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->setLayout(layout);

		m_VertexArray->addVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };

		Almond::Ref<Almond::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Almond::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->setIndexBuffer(m_IndexBuffer);

		//----

		m_SquareVA.reset(Almond::VertexArray::create());

		float Svertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Almond::Ref<Almond::VertexBuffer> sqaredVB;
		sqaredVB.reset(Almond::VertexBuffer::create(Svertices, sizeof(Svertices)));
		sqaredVB->setLayout({
			{Almond::ShaderDataType::Float3, "a_Position"},
			});


		m_SquareVA->addVertexBuffer(sqaredVB);
		uint32_t Sindices[] = { 0, 1, 2, 2, 3, 0 };
		Almond::Ref<Almond::IndexBuffer> sqaredIB;
		sqaredIB.reset(Almond::IndexBuffer::create(Sindices, sizeof(Sindices) / sizeof(uint32_t)));

		m_SquareVA->setIndexBuffer(sqaredIB);

		//----------

		std::string vertexSrc = R"(
			#version 330 core
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			layout(location=0) out vec4 color;
			uniform vec4 u_Color;
			
			
			void main()
			{
				color = u_Color;

			}
		)";

		m_Shader.reset(Almond::Shader::create(vertexSrc, fragmentSrc));


		std::string vertexSrc2 = R"(
			#version 330 core
			layout(location=0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			void main()
			{
				
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core

			layout(location=0) out vec4 color;
			
		
			void main()
			{
				color = vec4(1.0, 0.5, 0.3, 1.0);
			}
		)";

		m_Shader2.reset(Almond::Shader::create(vertexSrc2, fragmentSrc2));
	}

	void onUpdate(Almond::Timestep ts) override
	{
		float time = ts;

		if (Almond::Input::isKeyPressed(AL_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraSpeed * ts;
		}
		if (Almond::Input::isKeyPressed(AL_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraSpeed * ts;
		}
		if (Almond::Input::isKeyPressed(AL_KEY_UP))
		{
			m_CameraPosition.y += m_CameraSpeed * ts;
		}
		if (Almond::Input::isKeyPressed(AL_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraSpeed * ts;
		}
		if (Almond::Input::isKeyPressed(AL_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		if (Almond::Input::isKeyPressed(AL_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

	

		Almond::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Almond::RenderCommand::clear();
		
		m_Camera.setPosition(m_CameraPosition);
		m_Camera.setRotation(m_CameraRotation);

		Almond::Renderer::beginScene(m_Camera);

		
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		
		

		std::dynamic_pointer_cast<Almond::OpenGLShader>(m_Shader)->bind();
		std::dynamic_pointer_cast<Almond::OpenGLShader>(m_Shader)->uploadUniformFloat4("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int i = 0; i < 20; i++) {
				glm::vec3 pos(i * spacing, y * spacing, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				
				Almond::Renderer::submit(m_Shader, m_SquareVA, transform);
			}
		}
		
		Almond::Renderer::submit(m_Shader2, m_VertexArray);

		Almond::Renderer::endScene();
	}
	virtual void onImGuiRender(float fr) 
	{
		bool close = true;
		ImGui::Begin("Debug Window", &close);                          
             

		ImGui::SliderFloat("float", &spacing, 0.0f, 3.0f);            
		ImGui::ColorEdit3("clear color", glm::value_ptr(m_SquareColor)); 

		ImGui::Text("Avg FPS: %.1f FPS - (%.3f ms/frame)", fr, 1000 / fr);
		ImGui::End();
	}

	void onEvent(Almond::Event& event) override
	{
		
	}
	
private:
	Almond::Ref<Almond::Shader> m_Shader;
	Almond::Ref<Almond::VertexArray> m_VertexArray;
	Almond::Ref<Almond::Shader> m_Shader2;
	Almond::Ref<Almond::VertexArray> m_SquareVA;

	Almond::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_CameraSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.0f;
	float spacing = 0.11f;

	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
	
	
};


	class Sandbox : public Almond::Application
	{
	public:
		Sandbox()
		{
			pushLayer(new ExampleLayer());
		}
		~Sandbox()
		{

		}
	};

Almond::Application* Almond::createApplication()
{
	return new Sandbox();
}
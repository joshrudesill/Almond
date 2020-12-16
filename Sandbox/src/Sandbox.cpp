#include <Almond.h>



class ExampleLayer : public Almond::Layer 
{
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void onUpdate() override
	{
		AL_INFO("ExampleLayer::Update");
	}

	void onEvent(Almond::Event& event) override
	{
		AL_TRACE("{0}", event);
	}
};


class Sandbox : public Almond::Application
{
public: 
	Sandbox()
	{
		pushLayer(new ExampleLayer());
		pushOverlay(new Almond::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};
 
Almond::Application* Almond::createApplication()
{
	return new Sandbox();
}
#include <Almond.h>
#include "imgui/imgui.h"




class ExampleLayer : public Almond::Layer 
{
public:
	ExampleLayer()
		:Layer("Example")
	{
		
	}

	void onUpdate() override
	{
		
	}
	virtual void onImGuiRender() 
	{
	
	}

	void onEvent(Almond::Event& event) override
	{
		//AL_TRACE("{0}", event);
	}
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
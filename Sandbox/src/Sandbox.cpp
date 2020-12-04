#include <Almond.h>


class Sandbox : public Almond::Application
{
public: 
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};
 
Almond::Application* Almond::createApplication()
{
	return new Sandbox();
}
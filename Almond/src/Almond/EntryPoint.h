#pragma once

#ifdef AL_PLATFORM_WINDOWS

extern Almond::Application* Almond::createApplication();

int main(int argc, char** argv) 
{
	Almond::Log::Init();
	AL_CORE_INFO("Initialized core log");
	AL_INFO("Initialized app log");

	auto app = Almond::createApplication();
	app->run();
	delete app;

}

#endif
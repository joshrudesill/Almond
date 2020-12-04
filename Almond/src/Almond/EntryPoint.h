#pragma once

#ifdef AL_PLATFORM_WINDOWS

extern Almond::Application* Almond::createApplication();

int main(int argc, char** argv) {

	auto app = Almond::createApplication();
	app->run(); 
	delete app;

}

#endif
#pragma once

//Run this only on windows for now. TODO: Fix this and add multiplat support but super low priority
#ifdef CE_PLATFORM_WINDOWS

//External call to our client application
extern cEngine::Application* cEngine::CreateApplication();

int main(int argc, char** argv) {
	//We need to initialize our logging system
	cEngine::Log::Init();

	//Create the base application
	auto app = cEngine::CreateApplication();
	//Run it
	app->Run();
	//When done with running delete the app and free up memory
	delete app;
}
#endif
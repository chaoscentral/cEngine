#pragma once

//Run this only on windows for now. TODO: Fix this and add multiplat support but super low priority
#ifdef CE_PLATFORM_WINDOWS

//External call to our client application
extern cEngine::Application* cEngine::CreateApplication();

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//We need to initialize our logging system
	AllocConsole();
	cEngine::Log::Init();

	//Create the base application
	auto app = cEngine::CreateApplication();
	//Run it
	//When done with running delete the app and free up memory
	delete app;
}
#endif
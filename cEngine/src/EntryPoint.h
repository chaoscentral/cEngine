#pragma once

#ifdef CE_PLATFORM_WINDOWS

extern cEngine::Application* cEngine::CreateApplication();

int main(int argc, char** argv) {
	auto app = cEngine::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error cEngine only support Windows
#endif
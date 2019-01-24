#pragma once

#ifdef CE_PLATFORM_WINDOWS

extern cEngine::Application* cEngine::CreateApplication();

int main(int argc, char** argv) {
	cEngine::Log::Init();
	CE_CORE_WARN("Initialized Log");
	int a = 5;
	CE_INFO("Hello! Var={0}", a);

	auto app = cEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif
#include <cEngine.h>

class Sandbox : public cEngine::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

cEngine::Application* cEngine::CreateApplication() {
	Application* app;

	app = new Application();
	if (!app) {
		return NULL;
	}

	bool result = app->Init();
	if (result) {
		app->Run();
	}
	return app;
}
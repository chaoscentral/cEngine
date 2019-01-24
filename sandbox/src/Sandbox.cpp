#include <cEngine.h>

class Sandbox : public cEngine::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

cEngine::Application* cEngine::CreateApplication() {
	return new Sandbox();
}
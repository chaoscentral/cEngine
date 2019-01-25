#include <cEngine.h>

class Sandbox : public cEngine::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

cEngine::Application* cEngine::CreateApplication() {
	//This is the function handle that is called from within the DLL and allows us to talk back and forth
	//Trying out one of the new macros
	CE_WARN("Hello World! - This is a warning");
	//Return a new instance of Sandbox. Not much here at the moment.
	return new Sandbox();
}
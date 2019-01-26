#include <cEngine.h>

class GameLayer : public cEngine::Layer
{
public:
	//int updateCount = 0;

	GameLayer()
		: Layer("Sandbox") {}

	void OnUpdate() override
	{
		//Handle update events here
	}

	void OnEvent(cEngine::Event& event) override
	{
		//Handle events here
		CE_TRACE("{0}", event.ToString());

	}
};

class Sandbox : public cEngine::Application {
public:
	Sandbox() {
		PushLayer(new GameLayer());
	}

	~Sandbox() {

	}

	
};

cEngine::Application* cEngine::CreateApplication() {
	//This is the function handle that is called from within the DLL and allows us to talk back and forth
	//Trying out one of the new macros
	CE_INFO("Launching the DLL");
	//Return a new instance of Sandbox. Not much here at the moment.
	return new Sandbox();
}
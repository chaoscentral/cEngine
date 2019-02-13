#include <cEngine.h>



class GameLayer : public cEngine::Layer
{
	void GameLayer::OnAttach() 
	{
		CE_INFO("Layer attached!!!");
	}

	void GameLayer::OnDetach() 
	{
	}

	void GameLayer::OnUpdate()
	{
	}

	void GameLayer::OnEvent(cEngine::Event& event) 
	{
		if (event.GetEventType() == cEngine::EventType::KeyPressed) {
			
		}
		event.m_Handled = true;
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
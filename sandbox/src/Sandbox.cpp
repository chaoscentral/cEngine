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
		cEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<cEngine::KeyPressedEvent>(CE_BIND_EVENT_FN(GameLayer::OnKeyPressed));
		event.m_Handled = true;
	}

	bool GameLayer::OnKeyPressed(cEngine::KeyPressedEvent& e) {
		CE_INFO("{0}", e.GetKeyCode());
		return false;
	}
};

class Sandbox : public cEngine::Application {
public:
	Sandbox::Sandbox(cEngine::RenderType renderer)
		: cEngine::Application(renderer) {
		//do nothing for now
		PushLayer(new GameLayer());
		PushOverlay(new cEngine::ImGuiLayer());
	}

	Sandbox::~Sandbox() {

	}

};

cEngine::Application* cEngine::CreateApplication() {
	//This is the function handle that is called from within the DLL and allows us to talk back and forth
	//Trying out one of the new macros
	CE_INFO("Launching the DLL");
	//Return a new instance of Sandbox. Not much here at the moment.
	return new Sandbox(cEngine::RenderType::OpenGL);
}
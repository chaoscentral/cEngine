#include "cepch.h"
#include "Application.h"

#include "cEngine/Log.h"
#include <GLFW/glfw3.h>

namespace cEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		CE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		previousTime = glfwGetTime();
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		CE_CORE_TRACE("{0}", e.ToString());
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::Run() {
		while (m_Running)
		{
			//Need to setup a call to an actual game loop
			//So right now I got some hacky discreet code that figures out the current framerate and stores it into frameCount
			//Along with setting up the current frame buffer
			double currentTime = glfwGetTime();
			frameCount++;

			if (currentTime - previousTime >= 1.0)
			{
				frameCount = 0;
				previousTime = currentTime;
			}

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
		return;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		frameCount = 0;
		previousTime = 0.0;
		return true;
	}
}

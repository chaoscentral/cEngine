#include "cepch.h"
#include "Application.h"

#include "cEngine/Log.h"
#include <glad/glad.h>

namespace cEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application(Renderer renderer)
	{
		CE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		WindowProps wp;

		switch (renderer) {
		case DirectX:
			CE_CORE_INFO("Using DirectX Renderer");
			wp.Title = "cEngine";
			wp.Width = 1280;
			wp.Height = 720;
			m_Window = std::unique_ptr<Window>(Window::CreateDX());
			m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
			Run();
			break;
		case OpenGL:
			CE_CORE_INFO("Using OpenGL Renderer");
			m_Window = std::unique_ptr<Window>(Window::Create());
			m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
			Run();
			break;
		}
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
		CE_CORE_TRACE(e.ToString());
		EventDispatcher dispatcher(e);
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
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
		return;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}

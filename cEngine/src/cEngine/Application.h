#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace cEngine {
	enum RenderType {
		OpenGL = 0,
		DirectX
	};
	class CENGINE_API Application
	{
	public:
		Application(RenderType renderer);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance;  }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
		double previousTime;
		int frameCount = 0;
	};
	//Create a sort of callback function our client can use to get things started
	Application* CreateApplication();
}


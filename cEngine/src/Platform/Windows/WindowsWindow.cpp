#include "cepch.h"
#include "WindowsWindow.h"

#include "cEngine/Events/ApplicationEvent.h"
#include "cEngine/Events/MouseEvent.h"
#include "cEngine/Events/KeyEvent.h"

namespace cEngine
{
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props, OpenGL);
	}

	Window* Window::Create(const WindowProps& props, RenderType renderer) {
		switch (renderer) {
		case OpenGL:
			return new WindowsWindow(props, OpenGL);
		case DirectX:
			return new WindowsWindow(props, DirectX);
		}
	}

	WindowsWindow::WindowsWindow(const WindowProps& props, RenderType renderType)
	{
		m_renderType = renderType;
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		switch (m_renderType) {
		case DirectX:
			m_Renderer = new DXRenderer(m_Data);
			break;
		case OpenGL:
			m_Renderer = new GLRenderer(m_Data, props.Title, (int)props.Width, (int)props.Height);
			break;
		}
	}

	void WindowsWindow::Shutdown()
	{
		m_Renderer->Shutdown();
		
	}

	void WindowsWindow::OnUpdate()
	{
		m_Renderer->OnUpdate();
	}

	void WindowsWindow::SetBGColor(float r, float g, float b) {
		//nothing
	}

	void WindowsWindow::SetEventCallback(const EventCallbackFn & callback)
	{
		m_Renderer->SetEventCallback(callback);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Renderer->SetVSync(enabled);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Renderer->IsVSync();
	}
}
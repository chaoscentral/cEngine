#pragma once

#include "cEngine/Window.h"

#include "Platform/Renderers/GLRenderer.h"
#include "Platform/Renderers/DXRenderer.h"


namespace cEngine
{
	class WindowsWindow : public Window
	{
	public:
		LRESULT WindowsCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WindowsWindow(const WindowProps& props, RenderType renderType);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override;
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		void SetBGColor(float r, float g, float b);
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		Renderer* m_Renderer = nullptr;
		RenderType m_renderType;

		WindowData m_Data;
	};
}
#include "cepch.h"
#include "DirectXWindow.h"

#include "cEngine/Events/ApplicationEvent.h"
#include "cEngine/Events/MouseEvent.h"
#include "cEngine/Events/KeyEvent.h"

namespace cEngine {
	static bool s_DXInitialized = false;

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		DirectXWindow* winptr = (DirectXWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		if (winptr == NULL) {
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		else {
			return winptr->WindowsCallback(hwnd, msg, wParam, lParam);
		}
	}

	DirectXWindow::DirectXWindow(const WindowPropsWin32 & props)
	{
		const LPCWSTR pClassName = L"cEngine";

		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = nullptr;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = pClassName;
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);
		m_Window = CreateWindowEx(0, pClassName,
			props.Title,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			200,
			200,
			props.Width,
			props.Height,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

		if (m_Window == NULL) {
			CE_CORE_ERROR("Error initializing Window");
			return;
		}

		SetWindowLongPtr(m_Window, GWLP_USERDATA, (LONG_PTR)this);

		ShowWindow(m_Window, SW_SHOW);

		

		Init(props);
	}

	DirectXWindow::~DirectXWindow()
	{
		Shutdown();
	}

	Window* Window::CreateDX(const WindowPropsWin32& props)
	{
		return new DirectXWindow(props);
	}

	void DirectXWindow::OnUpdate()
	{
		MSG msg;
		BOOL gResult;
		if (gResult = GetMessage(&msg, m_Window, 0, 0) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void DirectXWindow::SetVSync(bool enabled)
	{
	}

	bool DirectXWindow::IsVSync() const
	{
		return false;
	}

	void DirectXWindow::SetBGColor(float r, float g, float b)
	{
	}

	LRESULT DirectXWindow::WindowsCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg) {
		case WM_CLOSE:
		{
			CE_CORE_INFO("Closing the application");
			WindowCloseEvent closeEvent;
			m_Data.EventCallback(closeEvent);
			//PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN:
		{
			int repeated = (lParam >> 30) & ((1 << 1) - 1);
			KeyPressedEvent kpEvent(wParam, repeated);
			m_Data.EventCallback(kpEvent);
			break;
		}
		case WM_KEYUP:
		{
			KeyReleasedEvent kuEvent(wParam);
			m_Data.EventCallback(kuEvent);
			break;
		}
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		{
			MouseButtonPressedEvent mbpEvent(wParam);
			m_Data.EventCallback(mbpEvent);
			break;
		}
		case WM_MOUSEMOVE:
		{
			POINTS pt = MAKEPOINTS(lParam);
			
			MouseMovedEvent mmEvent(pt.x, pt.y);
			m_Data.EventCallback(mmEvent);
		}
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);

	}

	void DirectXWindow::Init(const WindowPropsWin32 & props)
	{
		CE_CORE_INFO("DirectX Initializing!");
	}

	void DirectXWindow::Shutdown()
	{
	}
}

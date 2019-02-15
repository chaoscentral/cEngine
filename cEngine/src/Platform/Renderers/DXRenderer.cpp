#include "cepch.h"
#include "DXRenderer.h"

#include "cEngine/Events/ApplicationEvent.h"
#include "cEngine/Events/MouseEvent.h"
#include "cEngine/Events/KeyEvent.h"

namespace cEngine {
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		DXRenderer* winptr = (DXRenderer*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		if (winptr == NULL) {
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		else {
			return winptr->WindowsCallback(hwnd, msg, wParam, lParam);
		}
	}

	LRESULT DXRenderer::WindowsCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg) {
		case WM_CLOSE:
		{
			CE_CORE_INFO("Closing the application");
			WindowCloseEvent closeEvent;
			m_Data.EventCallback(closeEvent);
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

	DXRenderer::DXRenderer(WindowData data) 
	: m_Data(data)
	{
		Init();
	}

	DXRenderer::~DXRenderer() {

	}

	int DXRenderer::Init() {
		m_hInstance = GetModuleHandle(nullptr);
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hInstance;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = m_className;
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);

		RECT wr;
		wr.left = 0;
		wr.right = m_Data.Width;
		wr.top = 0;
		wr.bottom = m_Data.Height;
		if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false) == 0) {
			return -1;
		}
		m_hWnd = CreateWindowEx(0, m_className,
			L"Demo",
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			wr.right - wr.left,
			wr.bottom - wr.top,
			nullptr,
			nullptr,
			m_hInstance,
			nullptr);

		if (m_hWnd == NULL) {
			CE_CORE_ERROR("Error initializing Window");
			return -1;
		}
		//Set a pointer to this class for later use in our WinProc
		SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

		CE_CORE_INFO("Creating Swap Chain...");
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = m_hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = true;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
		D3D_FEATURE_LEVEL featureLevel;
		CE_CORE_INFO("Setting Feature Level...");
		const D3D_FEATURE_LEVEL featureLevelArray[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0
		};

		CE_CORE_INFO("Creating Device and Swap Chain");
		if (D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			createDeviceFlags,
			featureLevelArray,
			4,
			D3D11_SDK_VERSION,
			&sd, &g_pSwapChain,
			&g_pd3dDevice,
			&featureLevel,
			&m_d3dContext) != S_OK) {
			return E_FAIL;
		}

		CreateRenderTarget();
	}

	void DXRenderer::Shutdown() {
		CleanupRenderTarget();
		if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
		if (m_d3dContext) { m_d3dContext->Release(); m_d3dContext = NULL; }
		if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
		UnregisterClass(m_className, m_hInstance);
		DestroyWindow(m_hWnd);
	}

	void DXRenderer::OnUpdate() {
		MSG msg;
		BOOL gResult;
		if (gResult = GetMessage(&msg, m_hWnd, 0, 0) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		float clearColor[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
		m_d3dContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		m_d3dContext->ClearRenderTargetView(g_mainRenderTargetView, clearColor);

		g_pSwapChain->Present(1, 0);
	}

	void DXRenderer::SetVSync(bool enabled)
	{
	}

	bool DXRenderer::IsVSync()
	{
		return false;
	}

	void DXRenderer::CreateRenderTarget()
	{
		CE_CORE_INFO("Creating Render Target...");
		ID3D11Texture2D* pBackBuffer;
		g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
		pBackBuffer->Release();

		ShowWindow(m_hWnd, SW_SHOW);
	}
	void DXRenderer::CleanupRenderTarget()
	{
		if (g_mainRenderTargetView) {
			g_mainRenderTargetView->Release();
			g_mainRenderTargetView = NULL;
		}
	}
}
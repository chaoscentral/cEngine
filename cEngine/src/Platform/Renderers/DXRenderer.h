#pragma once

#include "Renderer.h"

#include "cEngine/Window.h"
#include "imgui.h"
#include "Platform/DirectX11/imgui_impl_dx11.h"
#include "Platform/DirectX11/imgui_impl_win32.h"
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

namespace cEngine {
	class DXRenderer : public Renderer {
	private:
		HWND m_hWnd;
		HINSTANCE m_hInstance;
		LPCWSTR m_className = L"cEngine";
		WindowData m_Data;

		ID3D11DeviceContext* m_d3dContext;
		ID3D11Device* g_pd3dDevice = NULL;
		IDXGISwapChain* g_pSwapChain = NULL;
		ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
	public:
		
		DXRenderer(WindowData data);
		~DXRenderer();
		int Init() override;
		void Shutdown() override;
		void OnUpdate() override;
		void SetVSync(bool enabled) override;
		bool IsVSync() override;
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		LRESULT WindowsCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		void CreateRenderTarget();
		void CleanupRenderTarget();
	};
}
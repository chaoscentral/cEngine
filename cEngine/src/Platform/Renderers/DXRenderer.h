#pragma once

#include "Renderer.h"
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

namespace cEngine {
	class DXRenderer : public Renderer {
	public:
		DXRenderer(HWND hWnd);
		~DXRenderer();
		int Init() override;
		void Shutdown() override;
		void OnUpdate() override;
		//Context* GetContext() override { return m_Context; }
	private:
		void CreateRenderTarget();
		void CleanupRenderTarget();
	private:
		HWND m_Window;
		//DXContext* m_Context;
		ID3D11DeviceContext* m_d3dContext;
		ID3D11Device* g_pd3dDevice = NULL;
		IDXGISwapChain* g_pSwapChain = NULL;
		ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
	};
}
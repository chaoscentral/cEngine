#include "cepch.h"
#include "DXRenderer.h"

namespace cEngine {
	DXRenderer::DXRenderer(HWND hWnd) 
	: m_Window(hWnd)
	{
		Init();
	}

	DXRenderer::~DXRenderer() {

	}

	int DXRenderer::Init() {
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
		sd.OutputWindow = m_Window;
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
	}

	void DXRenderer::OnUpdate() {
		float clearColor[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
		m_d3dContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		m_d3dContext->ClearRenderTargetView(g_mainRenderTargetView, clearColor);

		g_pSwapChain->Present(1, 0);
	}
	void DXRenderer::CreateRenderTarget()
	{
		CE_CORE_INFO("Creating Render Target...");
		ID3D11Texture2D* pBackBuffer;
		g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
		pBackBuffer->Release();
	}
	void DXRenderer::CleanupRenderTarget()
	{
		if (g_mainRenderTargetView) {
			g_mainRenderTargetView->Release();
			g_mainRenderTargetView = NULL;
		}
	}
}
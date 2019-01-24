#include "Graphics.h"

namespace cEngine {

	Graphics::Graphics()
	{
		m_D3D = 0;
	}

	Graphics::Graphics(const Graphics&) {

	}

	Graphics::~Graphics()
	{
	}

	bool Graphics::Init(int screenWidth, int screenHeight, HWND hwnd) {
		bool result;

		m_D3D = new D3DClass;
		if (!m_D3D) {
			return false;
		}

		result = m_D3D->Init(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
		if (!result) {
			MessageBox(hwnd, (LPCSTR)"Could not initialize Direct3D", (LPCSTR)"Error", MB_OK);
			return false;
		}
		return true;
	}

	void Graphics::Shutdown() {
		if (m_D3D) {
			m_D3D->Shutdown();
			delete m_D3D;
			m_D3D = 0;
		}
		return;
	}

	bool Graphics::Frame() {
		bool result;

		result = Render();
		if (!result) {
			return false;
		}
		return true;
	}

	bool Graphics::Render() {
		m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

		m_D3D->EndScene();
		return true;
	}

}
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

		//Update code in here I think let's find out?!
		float rVal = 0.005f;
		float bVal = 0.001f;
		float gVal = 0.007f;

		

		refreshR += rVal;
		refreshG += gVal;
		refreshB += bVal;

		if (refreshR >= 1.0f) rVal *= -1.0f;
		if (refreshG >= 1.0f) gVal *= -1.0f;
		if (refreshB >= 1.0f) bVal *= -1.0f;


		result = Render();
		if (!result) {
			return false;
		}
		return true;
	}

	bool Graphics::Render() {
		m_D3D->BeginScene(refreshR, refreshG, refreshB, 1.0f);

		m_D3D->EndScene();
		return true;
	}

}
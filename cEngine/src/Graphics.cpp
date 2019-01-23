#include "Graphics.h"

namespace cEngine {

	Graphics::Graphics()
	{
	}

	Graphics::Graphics(const Graphics&) {

	}

	Graphics::~Graphics()
	{
	}

	bool Graphics::Init(int screenWidth, int screenHeight, HWND hwnd) {
		return true;
	}

	void Graphics::Shutdown() {
		return;
	}

	bool Graphics::Frame() {
		return true;
	}

	bool Graphics::Render() {
		return true;
	}

}
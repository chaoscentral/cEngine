#pragma once

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <Windows.h>

namespace cEngine {

	const bool FULL_SCREEN = true;
	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 1000.0f;
	const float SCREEN_NEAR = 1.0f;

	class Graphics
	{
	public:
		Graphics();
		Graphics(const Graphics&);
		~Graphics();

		bool Init(int, int, HWND);
		void Shutdown();
		bool Frame();

	private:
		bool Render();
	};

}

#endif
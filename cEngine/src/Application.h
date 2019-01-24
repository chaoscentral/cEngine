#pragma once

#include "Core.h"
#include <Windows.h>
#include "Input.h"
#include "Graphics.h"

#define _SYSTEMCLASS_H_
#define WIN32_LEAN_AND_MEAN

namespace cEngine {
	class CENGINE_API Application
	{
	public:
		Application();
		Application(const Application&);
		~Application();

		bool Init();
		void Shutdown();
		void Run();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	private:
		bool Frame();
		void InitializeWindows(int&, int&);
		void ShutdownWindows();

	private:
		LPCSTR m_applicationName;
		HINSTANCE m_hInstance;
		HWND m_hWnd;

		Input* m_Input;
		Graphics* m_Graphics;

	};
	Application* CreateApplication();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static Application* ApplicationHandle = 0;
}


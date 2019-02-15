#pragma once

#include "cepch.h"

#include "Platform/Renderers/Renderer.h"

#include "cEngine/Core.h"
#include "cEngine/Events/Event.h"

namespace cEngine 
{
	enum RenderType {
		OpenGL = 0,
		DirectX
	};

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "cEngine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	struct WindowPropsWin32
	{
		LPCWSTR Title;
		unsigned int Width;
		unsigned int Height;

		WindowPropsWin32(LPCWSTR title = L"cEngine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;

		std::function<void(Event&)> EventCallback;
	};

	class CENGINE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props, RenderType renderer);
		static Window* Create(const WindowProps& props = WindowProps());
		static Window* CreateDX(const WindowPropsWin32& props = WindowPropsWin32());
	};
}
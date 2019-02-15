#include "cEngine/Window.h"

#include <Windows.h>


namespace cEngine
{
	class DirectXWindow : public Window
	{
	public:
		DirectXWindow(const WindowPropsWin32& props);
		virtual ~DirectXWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		void SetBGColor(float r, float g, float b);
		LRESULT CALLBACK WindowsCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		virtual void Init(const WindowPropsWin32& props);
		virtual void Shutdown();
	private:
		HWND m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
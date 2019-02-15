#pragma once

#include "Renderer.h"
#include "cEngine/Window.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#pragma comment(lib, "OpenGL32.lib")

namespace cEngine {
	class GLRenderer : public Renderer {
	public:
		GLRenderer(WindowData data, std::string title, int width, int height);
		~GLRenderer();
		int Init() override;
		void Shutdown() override;
		void SetVSync(bool enabled) override;
		bool IsVSync() override;
		void OnUpdate() override;

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
	private:
		static void CursorCallback(GLFWwindow * window, double xPos, double yPos);
		static void WindowSizeCallback(GLFWwindow * window, int width, int height);
		static void CloseCallback(GLFWwindow* window);
		static void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
		static void CharCallback(GLFWwindow * window, unsigned int keycode);
		static void MouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
		static void ScrollCallback(GLFWwindow * window, double xOffset, double yOffset);
	private:
		GLFWwindow* m_Window = NULL;
		WindowData m_Data;
	};
}
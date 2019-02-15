#include "cepch.h"
#include "GLRenderer.h"

#include "cEngine/Events/ApplicationEvent.h"
#include "cEngine/Events/MouseEvent.h"
#include "cEngine/Events/KeyEvent.h"

namespace cEngine {
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		CE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	GLRenderer::GLRenderer(WindowData data, std::string title, int width, int height) 
		:m_Data(data)
	{

		CE_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			CE_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			int maj, min, rev;
			glfwGetVersion(&maj, &min, &rev);
			CE_CORE_INFO("GLFW Version {0}.{1}.{2} Initialized!", maj, min, rev);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(data.Width, data.Height, data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CE_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		Init();
	}

	GLRenderer::~GLRenderer() {
		Shutdown();
	}

	void GLRenderer::WindowSizeCallback(GLFWwindow* window, int width, int height) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;

		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	}

	void GLRenderer::CursorCallback(GLFWwindow* window, double xPos, double yPos)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		data.EventCallback(event);
	}

	void GLRenderer::CloseCallback(GLFWwindow* window) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.EventCallback(event);
	}

	void GLRenderer::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent event(key, 0);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(key);
			data.EventCallback(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event(key, 1);
			data.EventCallback(event);
			break;
		}
		}
	}

	void GLRenderer::CharCallback(GLFWwindow* window, unsigned int keycode)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		KeyTypedEvent event(keycode);
		data.EventCallback(event);
	}

	void GLRenderer::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event(button);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event(button);
			data.EventCallback(event);
			break;
		}
		}
	}

	void GLRenderer::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
	}

	int GLRenderer::Init() {
		glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);
		glfwSetWindowCloseCallback(m_Window, CloseCallback);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetCharCallback(m_Window, CharCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetScrollCallback(m_Window, ScrollCallback);
		glfwSetCursorPosCallback(m_Window, CursorCallback);

		return 0;
	}

	void GLRenderer::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GLRenderer::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void GLRenderer::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool GLRenderer::IsVSync()
	{
		return m_Data.VSync;
	}
}
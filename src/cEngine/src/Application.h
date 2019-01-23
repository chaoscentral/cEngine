#pragma once

#include "Core.h"

namespace cEngine {
	class CENGINE_API Application
	{
	public:
		Application();
		~Application();
		void Run();
	};
	Application* CreateApplication();
}


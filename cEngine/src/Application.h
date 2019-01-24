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
	//Create a sort of callback function our client can use to get things started
	Application* CreateApplication();
}


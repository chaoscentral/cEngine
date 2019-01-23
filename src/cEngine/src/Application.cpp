#include "Application.h"
#include <stdio.h>

namespace cEngine {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run() {
		printf("Hello World");
		while (true);
	}

}
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
		//This is what happens when our application is run. Not very exciting for now
		printf("Hello World\n");
		//Infinite loop to keep the app open
		while (true);
		//finish
		return;
	}
}

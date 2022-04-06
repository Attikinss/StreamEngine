#include "StreamEngine.h"
#include <iostream>

int main(int argc, char** argv) {
	int runResult = 0;
	SE::Application* app = SE::Application::Create({ argc, argv });
	if (app->Initialize()) {
		app->Run();
		
		if (!app->Shutdown()) {
			//TODO: Present error
			runResult = 1;
		}
	}
	else {
		runResult = 1;
	}

	delete app;

	return 0;
}
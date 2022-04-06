#include "StreamEngine.h"

int main() {
	int runResult = 0;
	SE::Application* app = SE::Application::Create();
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
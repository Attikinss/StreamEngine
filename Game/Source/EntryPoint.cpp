#include "GameApplication.h"

int main() {
	int runResult = 0;
	GameApplication* app = new GameApplication();
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

	return 0;
}
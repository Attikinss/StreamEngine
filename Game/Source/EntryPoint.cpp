#include "StreamEngine.h"

int main(int argc, char** argv) {
	int runResult = 0;
	SE::Application* app = SE::Application::Create({ argv, argc });
	if (app->Initialize()) {
		app->Run();
		
		if (!app->Shutdown()) {
			SE::Logger::Critical("Failed to shutdown application correctly!");
			runResult = 1;
		}
	}
	else {
		SE::Logger::Critical("Failed to initialize application correctly!");
		runResult = 1;
	}

	delete app;
	return runResult;
}
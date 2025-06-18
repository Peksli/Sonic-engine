#include <Sonic.h>


class Sandbox_Application : public  Sonic::Application {
public:
	Sandbox_Application()
		:Sonic::Application() {}
};


Sonic::Application* Sonic::CreateApplication() {
	return new Sandbox_Application();
}


int main() {

	auto app = Sonic::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
#include "Macros.h"


namespace Sonic {

	class Application {
	public:
		Application();
		virtual ~Application();
		Application(Application&& app) = delete;
		Application(const Application& app) = delete;
		Application operator=(Application&& app) = delete;
		Application operator=(const Application& app) = delete;

		void Run();

		static Application* GetInstance() { return m_Instance; }
	private:
		static Application* m_Instance;
	};

	Application* CreateApplication();

}
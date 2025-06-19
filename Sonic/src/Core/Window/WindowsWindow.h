#include "Window/Window.h"


namespace Sonic {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(uint32_t width, uint32_t height, const char* title);
		~WindowsWindow();

		void Run() override;
		void OnUpdate() override;
	private:
		void OnInit() override;
		void OnDestroy() override;
	};

}
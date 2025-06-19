#include <GLFW/glfw3.h>


namespace Sonic {

	class Window {
	public:
		Window(uint32_t width, uint32_t height, const char* title);
		virtual ~Window();
		
		virtual void Run() = 0;
		virtual void OnUpdate() = 0;

		uint32_t GetWidth() const { return data.width; }
		uint32_t GetHeight() const { return data.height; }
		const char* GetTitle() const { return data.title; }

		void SetWidth(uint32_t width) { data.width = width; }
		void SetHeight(uint32_t height) { data.height = height; }
		void SetTitle(const char* title) { data.title = title; }
	protected:
		virtual void OnInit() = 0;
		virtual void OnDestroy() = 0;

		struct WindowData {
			GLFWwindow* window;
			uint32_t width;
			uint32_t height;
			const char* title;
		} data;
	};

}
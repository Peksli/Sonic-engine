#include "Window/WindowsWindow.h"


namespace Sonic {

	WindowsWindow::WindowsWindow(uint32_t width, uint32_t height, const char* title)
		: Window(width, height, title) {
		OnInit();
	}

	WindowsWindow::~WindowsWindow() {
		OnDestroy();
	}

	void WindowsWindow::Run() {
		while (!glfwWindowShouldClose(data.window)) {
			OnUpdate();
		}
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
	}

	void WindowsWindow::OnInit() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		data.window = glfwCreateWindow(data.width, data.height, data.title, nullptr, nullptr);
	}

	void WindowsWindow::OnDestroy() {
		glfwDestroyWindow(data.window);
		glfwTerminate();
	}

}
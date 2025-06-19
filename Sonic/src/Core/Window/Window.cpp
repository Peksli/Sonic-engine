#include "Window/Window.h"


namespace Sonic {

	Window::Window(uint32_t width, uint32_t height, const char* title)
		: data{nullptr, width, height, title}
	{

	}

	Window::~Window() {

	}

}
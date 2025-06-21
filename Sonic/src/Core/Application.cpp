#include "Application.h"
#include "Vulkan/VulkanContext.h"

namespace Sonic {

	Sonic::Application* Application::m_Instance = nullptr;

	Application::Application() {
		m_Instance = this;
		m_WindowsWindow = std::make_unique<WindowsWindow>(1400, 900, "Sonic window");
	}


	void Application::Run() {
		m_WindowsWindow->Run();
	}

	Application::~Application() {

	}

}
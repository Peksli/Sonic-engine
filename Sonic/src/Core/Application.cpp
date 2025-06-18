#include "Application.h"

namespace Sonic {

	Sonic::Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		m_Instance = this;
	}


	void Application::Run()
	{
		while (true);
	}

	Application::~Application()
	{

	}

}
#include "VulkanContext.h"

#include <GLFW/glfw3.h>

namespace Sonic {

	VulkanContext::VulkanContext() {
		CreateInstance();
		debugUtils.setupDebugMessenger(instance, &debugMessenger);
	}

	VulkanContext::~VulkanContext() {

	}

	void VulkanContext::CreateInstance() {
		if (!debugUtils.checkAvailableValidationLayers(validationLayers)) {
			throw std::runtime_error("Can not find validation layer");
		}
		VkInstanceCreateInfo createInfo = {};
		VkApplicationInfo appInfo = {};
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};

		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Vulkan";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = nullptr;
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_2;

		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();

		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = extensions.size();
		createInfo.ppEnabledExtensionNames = extensions.data();

		debugUtils.populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
			throw std::runtime_error("failed to create instance");
	}


	std::vector<const char*> VulkanContext::getRequiredExtensions() {
		uint32_t extensionsCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionsCount);
		for (uint32_t i = 0; i < extensionsCount; ++i) {
			std::cout << "Glfw extension: " << glfwExtensions[i] << '\n';
		}

		std::vector<const char*> extensions(glfwExtensions, extensionsCount + glfwExtensions);
		extensions.push_back("VK_EXT_debug_utils");
		for (const char* extension : extensions)
			std::cout << "Available extensions for instance: " << extension << std::endl;
		
		return extensions;
	}

}
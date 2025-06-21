#include "VulkanContext.h"

#include <GLFW/glfw3.h>

namespace Sonic {

	VulkanContext::VulkanContext() {
		CreateInstance();
		setupDebugMessenger();
	}

	VulkanContext::~VulkanContext() {

	}

	void VulkanContext::setupDebugMessenger() {
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
		populateDebugMessengerCreateInfo(debugCreateInfo);
		if (CreateDebugUtilsMessengerEXT(instance, &debugCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS)
			throw std::runtime_error("failed to set up debug messenger");
	}

	void VulkanContext::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo) {
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugCreateInfo.pfnUserCallback = debugCallback;
	}

	void VulkanContext::CreateInstance() {
		if (!checkAvailableValidationLayers()) {
			throw std::runtime_error("Can not find validation layer ERORR");
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

		populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
			throw std::runtime_error("failed to create instance");
	}

	bool VulkanContext::checkAvailableValidationLayers() {
		uint32_t layersCount = 0;
		vkEnumerateInstanceLayerProperties(&layersCount, nullptr);
		std::vector<VkLayerProperties> availableLayers(layersCount);
		vkEnumerateInstanceLayerProperties(&layersCount, availableLayers.data());

		for (const char* reqLayer : validationLayers) {
			auto itLayer = std::find_if(availableLayers.begin(), availableLayers.end(), [=](VkLayerProperties& layerProps) {
				return strcmp(reqLayer, layerProps.layerName) == 0;
				});
			if (itLayer == availableLayers.end()) { std::cout << "Didn't find layer: " << reqLayer << std::endl; return false; }

			std::cout << "Available layer: " << itLayer->layerName << std::endl;
		}

		return true;
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

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanContext::debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT messageType, 
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, 
		void* pUserData) 
	{
		std::cout << "[Custom Callback] Validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}

	VkResult VulkanContext::CreateDebugUtilsMessengerEXT(
		VkInstance instance, 
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
		const VkAllocationCallbacks* pAllocator, 
		VkDebugUtilsMessengerEXT* pDebugMessenger) 
	{
		auto Fn = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		return Fn
			? Fn(instance, pCreateInfo, pAllocator, pDebugMessenger)
			: VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	void VulkanContext::DestroyDebugUtilsMessengerEXT(
		VkInstance instance, 
		const VkDebugUtilsMessengerEXT* pDebugMessenger, 
		const VkAllocationCallbacks* pAllocator)
	{
		auto Fn = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (Fn != nullptr) {
			Fn(instance, debugMessenger, pAllocator);
		}
	}

}
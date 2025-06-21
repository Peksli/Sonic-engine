#include "Debug/VulkanDebugUtils.h"

#include "pch.h"


namespace Sonic {

	VulkanDebugUtils::VulkanDebugUtils() {

	}

	VulkanDebugUtils::~VulkanDebugUtils() {

	}

	void VulkanDebugUtils::setupDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT* debugMessenger) {
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
		this->populateDebugMessengerCreateInfo(debugCreateInfo);
		if (this->CreateDebugUtilsMessengerEXT(instance, &debugCreateInfo, nullptr, debugMessenger) != VK_SUCCESS)
			throw std::runtime_error("failed to set up debug messenger");
	}

	void VulkanDebugUtils::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo) {
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugCreateInfo.pfnUserCallback = debugCallback;
	}

	bool VulkanDebugUtils::checkAvailableValidationLayers(const std::vector<const char*>& validationLayers) {
		uint32_t layersCount = 0;
		vkEnumerateInstanceLayerProperties(&layersCount, nullptr);
		std::vector<VkLayerProperties> availableLayers(layersCount);
		vkEnumerateInstanceLayerProperties(&layersCount, availableLayers.data());

		for (const char* reqLayer : validationLayers) {
			auto itLayer = std::find_if(availableLayers.begin(), availableLayers.end(), [=](VkLayerProperties& layerProps) {
				return strcmp(reqLayer, layerProps.layerName) == 0;
				});
			if (itLayer == availableLayers.end()) { std::cout << "Didn't find layer: " << reqLayer << std::endl; return false; }

			std::cout << "Active layer: " << itLayer->layerName << std::endl;
		}

		return true;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugUtils::debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT messageType, 
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, 
		void* pUserData)
	{
		std::cout << "[Custom Callback] Validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}

	VkResult VulkanDebugUtils::CreateDebugUtilsMessengerEXT(
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

	void VulkanDebugUtils::DestroyDebugUtilsMessengerEXT(
		VkInstance instance, 
		const VkDebugUtilsMessengerEXT pDebugMessenger, 
		const VkAllocationCallbacks* pAllocator)
	{
		auto Fn = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (Fn != nullptr) {
			Fn(instance, pDebugMessenger, pAllocator);
		}
	}

}
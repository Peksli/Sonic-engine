#pragma once
#include <vulkan/vulkan.h>


namespace Sonic {

	class VulkanDebugUtils {
	public:
		VulkanDebugUtils();
		~VulkanDebugUtils();

		void setupDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT* debugMessenger);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo);
		bool checkAvailableValidationLayers(const std::vector<const char*>& validationLayers);
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
		VkResult CreateDebugUtilsMessengerEXT(
			VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(
			VkInstance instance,
			const VkDebugUtilsMessengerEXT pDebugMessenger,
			const VkAllocationCallbacks* pAllocator);
	};

}
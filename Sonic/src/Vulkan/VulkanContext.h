#include <vulkan/vulkan.h>

#include "pch.h"


namespace Sonic {

	class VulkanContext {
	public:
		VulkanContext();
		~VulkanContext();
	private:
		std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;

		void setupDebugMessenger();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo);
		void CreateInstance();
		bool checkAvailableValidationLayers();
		std::vector<const char*> getRequiredExtensions();
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
			const VkDebugUtilsMessengerEXT* pDebugMessenger,
			const VkAllocationCallbacks* pAllocator);
	};

}
#pragma once
#include <vulkan/vulkan.h>

#include "pch.h"
#include "Debug/VulkanDebugUtils.h"


namespace Sonic {

	class VulkanContext {
	public:
		VulkanContext();
		~VulkanContext();
	private:
		std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VulkanDebugUtils debugUtils;

		void CreateInstance();
		std::vector<const char*> getRequiredExtensions();
	};

}
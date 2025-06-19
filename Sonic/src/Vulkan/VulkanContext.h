#include <vulkan/vulkan.h>

#include "pch.h"


namespace Sonic {

	class VKContext {
	public:
		VKContext();
		~VKContext();
		void LogAvailableValidationLayers();
	private:
		uint32_t layersCount;
		std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
		std::vector<VkLayerProperties> availableLayers = {};
		VkInstance vkInstance;
		VkApplicationInfo appInfo = {};
		VkInstanceCreateInfo instanceInfo = {};

		void InitVkContext();
		void DestroyVkContext();
	};

}
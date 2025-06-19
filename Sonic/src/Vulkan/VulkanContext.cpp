#include "VulkanContext.h"


namespace Sonic {

	VKContext::VKContext() {
		InitVkContext();
	}

	VKContext::~VKContext() {
		DestroyVkContext();
	}

	void VKContext::LogAvailableValidationLayers() {
		for (const auto& layer : availableLayers) {
			std::cout << "LayerName: " << layer.layerName << std::endl;
		}
	}

	void VKContext::InitVkContext() {
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Vulkan";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = nullptr;
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_3;

		vkEnumerateInstanceLayerProperties(&layersCount, nullptr);
		availableLayers.resize(layersCount); 
		vkEnumerateInstanceLayerProperties(&layersCount, availableLayers.data());

		LogAvailableValidationLayers();

		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pApplicationInfo = &appInfo;
		instanceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		instanceInfo.ppEnabledLayerNames = validationLayers.data();

		VkResult result = vkCreateInstance(&instanceInfo, nullptr, &vkInstance);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("Failed to create Vulkan instance!");
		}
	}


	void VKContext::DestroyVkContext() {
		vkDestroyInstance(vkInstance, nullptr);
	}

}
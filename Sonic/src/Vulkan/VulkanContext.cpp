#include "VulkanContext.h"


namespace Sonic {

	VKContext::VKContext() {
		InitVkContext();
	}

	VKContext::~VKContext() {
		DestroyVkContext();
	}

	void VKContext::InitVkContext() {
		VkResult result = vkCreateInstance(&instanceInfo, nullptr, &vkInstance);

		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Vulkan";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = nullptr;
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_4;

		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pApplicationInfo = &appInfo;
	}

	void VKContext::DestroyVkContext() {
		vkDestroyInstance(vkInstance, nullptr);
	}

}
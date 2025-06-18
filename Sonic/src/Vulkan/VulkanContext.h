#include <vulkan/vulkan.h>


namespace Sonic {

	class VKContext {
	public:
		VKContext();
		~VKContext();
	private:
		VkInstance vkInstance;
		VkApplicationInfo appInfo = {};
		VkInstanceCreateInfo instanceInfo = {};

		void InitVkContext();
		void DestroyVkContext();
	};

}
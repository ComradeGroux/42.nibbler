#include "Graphics.hpp"

#include <glm/glm.hpp>
#include <SDL3/SDL_vulkan.h>
#include <SDL3/SDL.h>

#include <stdexcept>
#include <vector>

IGraphLib*	create(void)
{
	return new Graphics();
}

void	destroy(IGraphLib *glib)
{
	delete glib;
}

static inline void chk(VkResult result) {
	if (result != VK_SUCCESS)
		throw std::runtime_error("Vulkan failed");
}

#include <iostream>
Graphics::Graphics(void)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw std::runtime_error(SDL_GetError());
	if (!SDL_Vulkan_LoadLibrary(NULL))
		throw std::runtime_error(SDL_GetError());
	volkInitializeCustom((PFN_vkGetInstanceProcAddr)SDL_Vulkan_GetVkGetInstanceProcAddr());
	
	_createVkApplicationInfo();
	_createVkInstance();
	_createVkDevice();
}

Graphics::~Graphics(void)
{
	vkDestroyDevice(_device, nullptr);
	vkDestroyInstance(_instance, nullptr);
	volkFinalize();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_Quit();
}

void	Graphics::_createVkApplicationInfo(void)
{
	_appInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = nullptr,
		.pApplicationName = "nibbler - Vulkan",
		.applicationVersion = 1,
		.pEngineName = "nibblerVulkan",
		.engineVersion = 1,
		.apiVersion = VK_API_VERSION_1_3
	};
}

void	Graphics::_createVkInstance(void)
{
	uint32_t instanceExtensionsCount{ 0 };
	char const* const* instanceExtensions{ SDL_Vulkan_GetInstanceExtensions(&instanceExtensionsCount) };

	VkInstanceCreateInfo	instanceCI{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = nullptr,
		.flags = {},
		.pApplicationInfo = &_appInfo,
		.enabledLayerCount = {},
		.ppEnabledLayerNames = {},
		.enabledExtensionCount = instanceExtensionsCount,
		.ppEnabledExtensionNames = instanceExtensions,
	};
	chk(vkCreateInstance(&instanceCI, nullptr, &_instance));
	volkLoadInstance(_instance);
}

void	Graphics::_selectVkPhysicalDevice(void)
{
	uint32_t			physicalDevicesCount{ 0 };
	chk(vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount, nullptr));
	std::vector<VkPhysicalDevice>	physicalDevices(physicalDevicesCount);
	chk(vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount, physicalDevices.data()));

	VkPhysicalDeviceProperties2 deviceProperties{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
		.pNext = nullptr,
		.properties = {}
	};
	for (uint32_t i = 0; i < physicalDevicesCount; i++)
	{
		vkGetPhysicalDeviceProperties2(physicalDevices[i], &deviceProperties);
		if (deviceProperties.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			_physicalDevice = physicalDevices[i];
			break;
		}
		if (_physicalDevice == VK_NULL_HANDLE)
			_physicalDevice = physicalDevices[i];
	}
	if (_physicalDevice == VK_NULL_HANDLE)
		throw std::runtime_error("No Vulkan GPU compatible found");
}

void	Graphics::_createVkDevice(void)
{
	_selectVkPhysicalDevice();

	uint32_t	queueFamilyCount{ 0 };
	vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyCount, queueFamilies.data());
	
	uint32_t graphicsQueueFamily{ UINT32_MAX };
	for (uint32_t i = 0; i < queueFamilyCount; i++) {
		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			graphicsQueueFamily = i;
			break;
		}
	}
	if (!SDL_Vulkan_GetPresentationSupport(_instance, _physicalDevice, graphicsQueueFamily))
		throw std::runtime_error("No graphics queue family found");

	const float	priority = 1.0f;
	VkDeviceQueueCreateInfo	queueCI{
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.pNext = nullptr,
		.flags = {},
		.queueFamilyIndex = graphicsQueueFamily,
		.queueCount = 1,
		.pQueuePriorities = &priority
	};
	VkDeviceCreateInfo	deviceCI{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = nullptr,
		.flags = {},
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queueCI,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = 0,
		.ppEnabledExtensionNames = nullptr,
		.pEnabledFeatures = nullptr
	};
	chk(vkCreateDevice(_physicalDevice, &deviceCI, nullptr, &_device));
	volkLoadDevice(_device);
	vkGetDeviceQueue(_device, graphicsQueueFamily, 0, &_queue);
}



void	Graphics::render(const Level& lvl)
{
	(void)lvl;
}

t_keycode		Graphics::getInput(void)
{
	return E_NOTHING;
}

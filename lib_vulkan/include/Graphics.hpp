#pragma once

#include "IGraphLib.hpp"

#define VOLK_IMPLEMENTATION
#include <volk.h>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

extern "C" IGraphLib* 	create();
extern "C" void			destroy(IGraphLib *glib);

class Graphics : public IGraphLib {
	private:
		VkApplicationInfo	_appInfo;
		VkInstance			_instance{ VK_NULL_HANDLE };
		VkPhysicalDevice	_physicalDevice{ VK_NULL_HANDLE };
		VkDevice			_device{ VK_NULL_HANDLE };
		VkQueue				_queue{ VK_NULL_HANDLE };
		VkSurfaceKHR		_surface{ VK_NULL_HANDLE };
		VkSwapchainKHR		_swapchain{ VK_NULL_HANDLE };
		VkCommandPool		_commandPool{ VK_NULL_HANDLE };

		enum E_Pipeline {
			E_PIPELINE_UI,
			E_PIPELINE_GAME,
			E_PIPELINE_COUNT
		};
		std::array<VkPipeline, E_PIPELINE_COUNT>		_pipelines;
		std::array<VkPipelineLayout, E_PIPELINE_COUNT>	_pipelineLayouts;

		const static uint32_t							_maxFramesInFlight = 2;
		std::array<VkCommandBuffer, _maxFramesInFlight>	_commandBuffers;

		VkFormat					_imageFormat = VK_FORMAT_R8G8B8A8_SRGB;
		std::vector<VkImage>		_swapchainImages;
		std::vector<VkImageView>	_swapchainImageViews;

		std::array<VkSemaphore, _maxFramesInFlight>	_semImageAvailable;
		std::array<VkSemaphore, _maxFramesInFlight>	_semRenderFinished;
		std::array<VkFence, _maxFramesInFlight>		_fenInFlight;
		uint32_t									_currentFrame = 0;

		VmaAllocator		_allocator{ VK_NULL_HANDLE };

		SDL_Window*			_window = nullptr;
		glm::ivec2			_windowSize;
		bool				_hasValidationLayer = false;
		float				_decorationHeight = 30.0f;

		void	_createVkApplicationInfo(void);
		void	_createVkInstance(void);
		void	_selectVkPhysicalDevice(void);
		void	_createVkDeviceAndQueue(void);
		void	_createAllocator(void);
		void	_createWindowAndSurface(void);
		void	_createSwapchain(void);
		void	_createSwapchainImages(void);
		void	_createSyncObjects(void);

		void	_createPipeline(void);
		void	_createUIPipeline(void);
		void	_createGamePipeline(void);

		static SDL_HitTestResult	_hitTestCallback(SDL_Window* win, const SDL_Point* area, void* data);

		void	_renderUI(VkCommandBuffer cmdBuff);
		void	_renderGame(VkCommandBuffer cmdBuff, const Level& lvl);

	public:
		Graphics(void);
		~Graphics(void);

		void		render(const Level& lvl);
		t_keycode	getInput(void);
};

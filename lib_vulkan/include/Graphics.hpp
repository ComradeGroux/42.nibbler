#pragma once

#include "IGraphLib.hpp"

#define VOLK_IMPLEMENTATION
#include <volk.h>

extern "C" IGraphLib* 	create();
extern "C" void			destroy(IGraphLib *glib);

class Graphics : public IGraphLib {
	private:
		VkApplicationInfo	_appInfo;
		VkInstance			_instance{ VK_NULL_HANDLE };
		VkPhysicalDevice	_physicalDevice{ VK_NULL_HANDLE };
		VkDevice			_device{ VK_NULL_HANDLE };
		VkQueue				_queue{ VK_NULL_HANDLE };

		void	_createVkApplicationInfo(void);
		void	_createVkInstance(void);
		void	_selectVkPhysicalDevice(void);
		void	_createVkDevice(void);

	public:
		Graphics(void);
		~Graphics(void);

		void		render(const Level& lvl);
		t_keycode	getInput(void);
};

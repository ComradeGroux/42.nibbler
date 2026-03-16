#pragma once

#include "IGraphLib.hpp"

#include <vulkan/vulkan.h>

extern "C" IGraphLib* 	create();
extern "C" void			destroy(IGraphLib *glib);

class Graphics : public IGraphLib {
	private:

	public:
		Graphics(void);
		~Graphics(void);

		void	clear(void);
		void	drawSnake(void);
		void	drawFood(void);
		void	render(void);
		int		getInput(void);
};

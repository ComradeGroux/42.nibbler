#pragma once

#include "IGraphLib.hpp"

#include <GLFW/glfw3.h>

extern "C" IGraphLib* 	create();
extern "C" void			destroy(IGraphLib *glib);

class Graphics : public IGraphLib {
	private:

	public:
		Graphics(void);
		~Graphics(void);

		void		render(const Level& lvl);
		t_keycode	getInput(void);
};

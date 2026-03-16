#pragma once

#include "Level.hpp"
#include "keycode.h"

class IGraphLib {
	public:
		virtual ~IGraphLib(void) = default;

		virtual void		clear() = 0;
		virtual void		drawSnake() = 0;
		virtual void		drawFood() = 0;
		virtual void		render(const Level& lvl) = 0;
		virtual t_keycode	getInput() = 0;
};

#pragma once

#include "Level.hpp"
#include "keycode.h"

class IGraphLib {
	public:
		virtual ~IGraphLib(void) = default;

		virtual void		render(const Level& lvl) = 0;
		virtual t_keycode	getInput() = 0;
};

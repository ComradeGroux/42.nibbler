#pragma once

#include "Level.hpp"
#include "keycode.h"

class IGraphLib {
	public:
		IGraphLib(void) = default;
		virtual ~IGraphLib(void) = default;

		IGraphLib(const IGraphLib&) = delete;
        IGraphLib& operator=(const IGraphLib&) = delete;

		virtual void		render(const Level& lvl) = 0;
		virtual t_keycode	getInput() = 0;
};

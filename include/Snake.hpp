#pragma once

#include "LibLoader.hpp"
#include "Level.hpp"

class Snake
{
	private:
		LibLoader	_loader;
		Level		_level;

	public:
		Snake(int width, int height, char *lib_name);
		Snake(const Snake& src);
		Snake	operator=(const Snake& src);
		~Snake(void);
	
		void	start(void);
};

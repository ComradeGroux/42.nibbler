#pragma once

#include "Level.hpp"
#include "LibLoader.hpp"

class Snake
{
	private:
		Level		_level;
		LibLoader	_loader;

	public:
		Snake(int width, int height, char *lib_name);
		Snake(const Snake& src);
		Snake&	operator=(const Snake& src);
		~Snake(void);
	
		void	start(void);
};

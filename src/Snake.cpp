#include "Snake.hpp"

Snake::Snake(int width, int height, char *lib_name) : _level(width, height)
{
	_loader.load(lib_name);
}

Snake::Snake(const Snake& src) : _level(src._level)
{
	_loader = src._loader;
}

Snake&	Snake::operator=(const Snake& src)
{
	if (this == &src)
		return *this;

	_loader = src._loader;
	_level = src._level;

	return *this;
}

Snake::~Snake(void)
{
}

void	Snake::start(void)
{
	_level.generateFood();
	_level.render();
}

#include "Snake.hpp"

#include "setting.h"

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

void	Snake::_handleInput(e_keycode input)
{
	switch (input)
	{
		case E_KEY_ONE:
			_loader.load(LIB1);
			break;
		case E_KEY_TWO:
			_loader.load(LIB2);
			break;
		case E_KEY_THREE:
			_loader.load(LIB3);
			break;
		default:
			break;
	}
}

void	Snake::start(void)
{
	_level.generateFood();
	while (_loader.get()->getInput() != E_KEY_ESC)
	{
		_handleInput(_loader.get()->getInput());

		_loader.get()->clear();
		_loader.get()->render(_level);
	}
}

#include "Snake.hpp"
#include "setting.h"

#include <unistd.h>
#include <iostream>
#include <chrono>

Snake::Snake(int width, int height, char *lib_name) : _level(width, height)
{
	_loader.load(lib_name);
	if (width > height)
		_direction = EAST;
	else
		_direction = SOUTH;

	std::pair<int, int>	p;
	int	x = width / 2;
	int	y = height / 2;
	for (unsigned int i = 4; i > 0; i--)
	{
		if (width > height)
		{
			p.first = x - i;
			p.second = y;
		}
		else
		{
			p.first = x;
			p.second = y - i;
		}
		_level.setCell(p.first, p.second, Level::E_SNAKE);
		_pos.push(p);
	}

	_pause = true;
}

Snake::Snake(const Snake& src) : _level(src._level)
{
	_loader = src._loader;
	_direction = src._direction;
	_pos = src._pos;
}

Snake&	Snake::operator=(const Snake& src)
{
	if (this == &src)
		return *this;

	_loader = src._loader;
	_level = src._level;
	_direction = src._direction;
	_pos = src._pos;

	return *this;
}

Snake::~Snake(void)
{
}

void	Snake::_handleLibInput(t_keycode input)
{
	switch (input)
	{
		case E_KEY_ONE:
			_pause = true;
			_loader.load(LIB1);
			break;
		case E_KEY_TWO:
			_pause = true;
			_loader.load(LIB2);
			break;
		case E_KEY_THREE:
			_pause = true;
			_loader.load(LIB3);
			break;
		default:
			_pause = false;
			break;
	}
}

void	Snake::_handleMovementInput(t_keycode input, t_facing& precedent)
{
	switch (input)
	{
		case E_KEY_UP:
			_pause = false;
			if (precedent == NORTH || precedent == SOUTH || _direction == NORTH || _direction == SOUTH)
				break;
			_direction = NORTH;
			break;
		case E_KEY_RIGHT:
			_pause = false;
			if (precedent == EAST || precedent == WEST || _direction == EAST || _direction == WEST)
				break;
			_direction = EAST;
			break;
		case E_KEY_DOWN:
			_pause = false;
			if (precedent == SOUTH || precedent == NORTH || _direction == SOUTH || _direction == NORTH)
				break;
			_direction = SOUTH;
			break;
		case E_KEY_LEFT:
			_pause = false;
			if (precedent == WEST || precedent == EAST || _direction == WEST || _direction == EAST)
				break;
			_direction = WEST;
			break;
		default:
			break;
	}
}

int	Snake::_move(void)
{
	std::pair<int, int>	p = _pos.back();
	switch (_direction)
	{
		case NORTH:
			p.second -= 1;
			break;
		case EAST:
			p.first += 1;
			break;
		case SOUTH:
			p.second += 1;
			break;
		case WEST:
			p.first -= 1;
			break;
		default:
			break;
	}
	Level::t_cell	cell = _level.getCell(p.first, p.second);
	if (cell == Level::E_WALL || cell == Level::E_SNAKE)
		return -1;
	else if (cell == Level::E_FOOD)
	{
		_level.setCell(p.first, p.second, Level::E_SNAKE);
		_pos.push(p);
		_level.generateFood();
		return 1;
	}
	_level.setCell(p.first, p.second, Level::E_SNAKE);
	_pos.push(p);

	p = _pos.front();
	_pos.pop();
	_level.setCell(p.first, p.second, Level::E_EMPTY);
	return 0;
}

inline void	Snake::_update(t_keycode& input)
{
	static t_facing									precedent = _direction;
	static std::chrono::steady_clock::time_point	lastTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point			currentTime = std::chrono::steady_clock::now();

	std::chrono::duration<float>		elapsed = currentTime - lastTime;

	input = _loader.get()->getInput();
	_handleLibInput(input);
	_handleMovementInput(input, precedent);
	_loader.get()->render(_level);

	if (_pause == false && std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() > SPEED_MS)
	{
		if (_move() == -1)
		{
			_loader.unload();
			std::cout << BRED << "You died" << CRESET << std::endl;
			input = E_KEY_ESC;
		}
		lastTime = currentTime;
		precedent = _direction;
	}
}

void	Snake::start(void)
{
	_level.generateFood();

	t_keycode	input = E_NOTHING;
	while (input != E_KEY_ESC)
		_update(input);
}

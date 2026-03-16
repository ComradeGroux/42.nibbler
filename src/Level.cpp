#include "Level.hpp"

Level::Level(int width, int height) : _width(width), _height(height), _board(nullptr), _random_engine(std::random_device{}())
{
	_board = new t_cell[_width * _height];

	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			if (x == 0 || x == _width - 1)
				setCell(x, y, E_WALL);
			else if (y == 0 || y == _height - 1)
				setCell(x, y, E_WALL);
			else
				setCell(x, y, E_EMPTY);
		}
	}
}

Level::Level(const Level& src)
{
	_width = src._width;
	_height = src._height;
	_random_engine = src._random_engine;

	_board = new t_cell[_width * _height];
	std::copy(src._board, src._board + (_width * _height), _board);
}

Level&	Level::operator=(const Level& src)
{
	if (this == &src)
		return *this;

	_width = src._width;
	_height = src._height;
	_random_engine = src._random_engine;

	delete[] _board;
	_board = new t_cell[_width * _height];
	std::copy(src._board, src._board + (_width * _height), _board);

	return *this;
}

Level::~Level(void)
{
	delete[] _board;
}

int	Level::getWidth(void) const
{
	return _width;
}

int	Level::getHeight(void) const
{
	return _height;
}

Level::t_cell	Level::getCell(int x, int y) const
{
	if (x >= _width || y >= _height)
		return E_WALL;

	return _board[x + (y * _width)];
}

void	Level::setCell(int x, int y, t_cell cell)
{
	if (x >= _width || y >= _height)
		return;

	_board[x + y * _width] = cell;
}

void	Level::generateFood(void)
{
	std::uniform_int_distribution<int>	distX(1, _width - 1);
	std::uniform_int_distribution<int>	distY(1, _height - 1);

	int x = 0;
	int y = 0;
	while (getCell(x, y) == E_WALL || getCell(x, y) != E_EMPTY)
	{
		x = distX(_random_engine);
		y = distY(_random_engine);
	}

	setCell(x, y, E_FOOD);
}

#include <iostream>
#include "ANSI-color-codes.h"
void	Level::render(void) const
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			if (getCell(x, y) == E_WALL)
				std::cout << BLUB << "W" << CRESET;
			else if (getCell(x, y) == E_EMPTY)
				std::cout << YEL << "." << CRESET;
			else if (getCell(x, y) == E_SNAKE)
				std::cout << GRNB << "S" << CRESET;
			else if (getCell(x, y) == E_FOOD)
				std::cout << REDHB << "F" << CRESET;
		}
		std::cout << std::endl;
	}
}

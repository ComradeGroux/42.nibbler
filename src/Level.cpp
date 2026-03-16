#include "Level.hpp"

Level::Level(int width, int height) : _width(width), _height(height)
{
	_board = new t_cell[_width * _height];

	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			if (x == 0 || x == _width - 1)
				_board[x + y * _width] = E_WALL;
			else if (y == 0 || y == _height - 1)
				_board[x + y * _width] = E_WALL;
			else
				_board[x + y * _width] = E_EMPTY;
		}
	}
}

Level::Level(const Level& src)
{
	_width = src._width;
	_height = src._height;
}

Level	Level::operator=(const Level& src)
{
	_width = src._width;
	_height = src._height;

	return *this;
}

Level::~Level(void)
{
	delete[] _board;
}

Level::t_cell	Level::getCell(int x, int y) const
{
	return _board[x + y * _width];
}

void	Level::setCell(int x, int y, t_cell cell)
{
	_board[x + y * _width] = cell;
}

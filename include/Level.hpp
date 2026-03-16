#pragma once

#include <random>

class Level
{
	public:
		typedef enum e_cell {
			E_WALL,
			E_EMPTY,
			E_FOOD,
			E_SNAKE
		} t_cell;

	private:
		int		_width;
		int		_height;
		t_cell*	_board;

		std::mt19937	_random_engine;

	public:
		Level(int width, int height);
		Level(const Level& src);
		Level&	operator=(const Level& src);
		~Level(void);

		t_cell	getCell(int x, int y) const;
		void	setCell(int x, int y, t_cell cell);

		void	generateFood(void);

		void	render(void) const;
};

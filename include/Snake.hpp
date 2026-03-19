#pragma once

#include "Level.hpp"
#include "LibLoader.hpp"

#include <queue>

class Snake
{
	private:
		typedef enum	e_facing {
			NORTH,
			EAST,
			SOUTH,
			WEST
		} t_facing;

		Level		_level;
		LibLoader	_loader;

		t_facing						_direction;
		std::queue<std::pair<int, int>>	_pos;

		bool	_pause;

		void	_handleLibInput(t_keycode input);
		void	_handleMovementInput(t_keycode input, t_facing& precedent);
		int		_move(void);
		void	_update(t_keycode& input);

	public:
		Snake(int width, int height, char *lib_name);
		Snake(const Snake& src);
		Snake&	operator=(const Snake& src);
		~Snake(void);
	
		void	start(void);
};

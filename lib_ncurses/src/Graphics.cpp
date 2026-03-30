#include "Graphics.hpp"

#include <unistd.h>

#define WALL_COLOR	1
#define FOOD_COLOR	2
#define SNAKE_COLOR	3
#define HEAD_COLOR	4

IGraphLib*	create(void)
{
	return new Graphics();
}

void	destroy(IGraphLib *glib)
{
	delete glib;
}

static inline void	initColors(void)
{
	start_color();
	init_pair(WALL_COLOR, COLOR_WHITE, COLOR_WHITE);
	init_pair(FOOD_COLOR, COLOR_RED, COLOR_RED);
	init_pair(SNAKE_COLOR, COLOR_GREEN, COLOR_GREEN);
	init_pair(HEAD_COLOR, COLOR_BLACK, COLOR_GREEN);
}

Graphics::Graphics(void)
{
	initscr();
	cbreak();
	noecho();
	nonl();
	keypad(stdscr, true);
	intrflush(stdscr, false);
	nodelay(stdscr, true);
	curs_set(0);
	initColors();
}

Graphics::~Graphics(void)
{
	endwin();
}

void	Graphics::render(const Level& lvl)
{
	werase(stdscr);

	int	width = lvl.getWidth();
	int	height = lvl.getHeight();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			switch (lvl.getCell(x, y))
			{
				case Level::E_EMPTY:
					addstr("  ");
					break;
				case Level::E_WALL:
					attron(COLOR_PAIR(WALL_COLOR));
					addstr("  ");
					attroff(COLOR_PAIR(WALL_COLOR));
					break;
				case Level::E_FOOD:
					attron(COLOR_PAIR(FOOD_COLOR));
					addstr("  ");
					attroff(COLOR_PAIR(FOOD_COLOR));
					break;
				case Level::E_SNAKE:
					attron(COLOR_PAIR(SNAKE_COLOR));
					addstr("  ");
					attroff(COLOR_PAIR(SNAKE_COLOR));
					break;
				default:
					break;
			}
		}
		addch('\n');
	}
	refresh();
}

t_keycode	Graphics::getInput(void)
{
	int	c = getch();

	switch (c)
	{
		case KEY_EXIT:
		case 27:
			return E_KEY_ESC;
		case '1':
			return E_KEY_ONE;
		case '2':
			return E_KEY_TWO;
		case '3':
			return E_KEY_THREE;
		case KEY_UP:
		case 'w':
		case 'W':
			return E_KEY_UP;
		case KEY_RIGHT:
		case 'd':
		case 'D':
			return E_KEY_RIGHT;
		case KEY_DOWN:
		case 's':
		case 'S':
			return E_KEY_DOWN;
		case KEY_LEFT:
		case 'a':
		case 'A':
			return E_KEY_LEFT;

		default:
			return E_NOTHING;
	}
}

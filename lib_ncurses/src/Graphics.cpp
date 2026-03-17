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
	keypad(stdscr, TRUE);
	intrflush(stdscr, FALSE);
	halfdelay(5);
	curs_set(0);
	initColors();
}

Graphics::~Graphics(void)
{
	endwin();
}

void	Graphics::render(const Level& lvl)
{
	wclear(stdscr);

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

	if (c == KEY_EXIT)
		return E_KEY_ESC;
	else if (c == 27)
		return E_KEY_ESC;
	else if (c == '1')
		return E_KEY_ONE;
	else if (c == '2')
		return E_KEY_TWO;
	else if (c == '3')
		return E_KEY_THREE;
	else if (c == KEY_UP || c == 'w' || c == 'W')
		return E_KEY_UP;
	else if (c == KEY_RIGHT || c == 'd' || c == 'D')
		return E_KEY_RIGHT;
	else if (c == KEY_DOWN || c == 's' || c == 'S')
		return E_KEY_DOWN;
	else if (c == KEY_LEFT || c == 'a' || c == 'A')
		return E_KEY_LEFT;

	return E_NOTHING;
}

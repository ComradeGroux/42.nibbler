#include "Graphics.hpp"

IGraphLib*	create(void)
{
	return new Graphics();
}

void	destroy(IGraphLib *glib)
{
	delete glib;
}

Graphics::Graphics(void)
{
}

Graphics::~Graphics(void)
{
}

void	Graphics::render(const Level& lvl)
{
	(void)lvl;
}

t_keycode		Graphics::getInput(void)
{
	return E_NOTHING;
}

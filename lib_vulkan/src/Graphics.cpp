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

#include <iostream>
void	Graphics::clear(void)
{
	std::cout << "TEST FROM vulkan" << std::endl;
}

void	Graphics::drawSnake(void)
{
}

void	Graphics::drawFood(void)
{
}

void	Graphics::render(void)
{
}

int		Graphics::getInput(void)
{
	return -1;
}

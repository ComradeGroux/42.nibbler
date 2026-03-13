#pragma once

class IGraphLib {
	public:
		virtual ~IGraphLib(void) = default;

		virtual void clear() = 0;
		virtual void drawSnake() = 0;
		virtual void drawFood() = 0;
		virtual void render() = 0;
		virtual int  getInput() = 0;
};

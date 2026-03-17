
#pragma once

#include "IGraphLib.hpp"

#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

extern "C" IGraphLib* 	create();
extern "C" void			destroy(IGraphLib *glib);

class Graphics : public IGraphLib {
	private:
		GLFWwindow*	_window;
		int			_width;
		int			_height;

		GLuint	_vao;
		GLuint	_vbo;
		GLuint	_shaderProgram;
		GLint	_colorUniform;
		GLint	_modelUniform;
		GLint	_projectionUniform;

		void	_initShaders(void);
		void	_initBuffers(void);

	public:
		Graphics(void);
		Graphics(const Graphics& src);
		Graphics&	operator=(const Graphics& src);
		~Graphics(void);

		void		render(const Level& lvl);
		t_keycode	getInput(void);
};

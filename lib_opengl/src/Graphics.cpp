
#include "Graphics.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

IGraphLib*	create(void)
{
	return new Graphics();
}

void	destroy(IGraphLib *glib)
{
	delete glib;
}

static const char* VERT_SRC = R"(
#version 460 core
layout(location = 0) in vec2 aPos;
uniform mat4 uProjection;
uniform mat4 uModel;
void main()
{
	gl_Position = uProjection * uModel * vec4(aPos, 0.0, 1.0);
}
)";

static const char* FRAG_SRC = R"(
#version 460 core
uniform vec3 uColor;
out vec4 fragColor;
void main()
{
	fragColor = vec4(uColor, 1.0);
}
)";

static const float UNIT_QUAD[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
};

Graphics::Graphics(void)
{
	_width = 800;
	_height = 600;
	if (!glfwInit())
		throw std::runtime_error("GLFW init failed");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	_window = glfwCreateWindow(_width, _height, "nibbler - OpenGL", NULL, NULL);
	if (!_window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create the window");
	}

	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
		throw std::runtime_error("GLAD init failed");
	}

	glfwSwapInterval(1);

	_initBuffers();
	_initShaders();
}

Graphics::~Graphics(void)
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteProgram(_shaderProgram);

	glfwDestroyWindow(_window);
	glfwTerminate();
}

static GLuint	compileShader(GLenum type, const char* src)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint ok;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	if (!ok)
	{
		char log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);
		glDeleteShader(shader);
		throw std::runtime_error(std::string("Shader compile error: ") + log);
	}
	return shader;
}

void	Graphics::_initShaders(void)
{
	GLuint vert = compileShader(GL_VERTEX_SHADER, VERT_SRC);
	GLuint frag = compileShader(GL_FRAGMENT_SHADER, FRAG_SRC);

	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vert);
	glAttachShader(_shaderProgram, frag);
	glLinkProgram(_shaderProgram);

	GLint ok;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &ok);
	if (!ok)
	{
		char log[512];
		glGetProgramInfoLog(_shaderProgram, 512, nullptr, log);
		glDeleteProgram(_shaderProgram);
		throw std::runtime_error(std::string("Shader link error: ") + log);
	}

	glDeleteShader(vert);
	glDeleteShader(frag);

	_colorUniform = glGetUniformLocation(_shaderProgram, "uColor");
	_modelUniform = glGetUniformLocation(_shaderProgram, "uModel");
	_projectionUniform = glGetUniformLocation(_shaderProgram, "uProjection");
}

void	Graphics::_initBuffers(void)
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UNIT_QUAD), UNIT_QUAD, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void	Graphics::render(const Level& lvl)
{
	glfwGetFramebufferSize(_window, &_width, &_height);
	glViewport(0, 0, _width, _height);
	glClear(GL_COLOR_BUFFER_BIT);

	int	width = lvl.getWidth();
	int	height = lvl.getHeight();

	float	drawScale = static_cast<float>(_width) / static_cast<float>(width);
	if (drawScale > static_cast<float>(_height) / static_cast<float>(height))
		drawScale = static_cast<float>(_height) / static_cast<float>(height);

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(_width), static_cast<float>(_height), 0.0f);

	glUseProgram(_shaderProgram);
	glBindVertexArray(_vao);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			switch (lvl.getCell(x, y))
			{
				case Level::E_EMPTY:
					glUniform3f(_colorUniform, 0.1f, 0.1f, 0.1f);
					break;
				case Level::E_WALL:
					glUniform3f(_colorUniform, 1.0f, 1.0f, 1.0f);
					break;
				case Level::E_FOOD:
					glUniform3f(_colorUniform, 1.0f, 0.2f, 0.2f);
					break;
				case Level::E_SNAKE:
					glUniform3f(_colorUniform, 0.2f, 0.9f, 0.2f);
					break;
				default:
					continue;
			}

			glm::mat4	model = glm::translate(glm::mat4(1.0f), glm::vec3(x * drawScale, y * drawScale, 0.0f));
			model = glm::scale(model, glm::vec3(drawScale, drawScale, 1.0f));

			glUniformMatrix4fv(_modelUniform, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(_projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}

	glBindVertexArray(0);
	glUseProgram(0);

	glfwSwapBuffers(_window);
}

t_keycode		Graphics::getInput(void)
{
	glfwPollEvents();

	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		return E_KEY_ESC;
	else if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS)
		return E_KEY_ONE;
	else if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS)
		return E_KEY_TWO;
	else if (glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS)
		return E_KEY_THREE;
	else if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		return E_KEY_UP;
	else if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		return E_KEY_RIGHT;
	else if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		return E_KEY_DOWN;
	else if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		return E_KEY_LEFT;

	return E_NOTHING;
}

TARGET := lib_opengl.so

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
OBJS_DIR := $(BUILD_DIR)/objs
DEPS_DIR := lib

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
VPATH := $(dir $(SRCS))
OBJS := $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.cpp=.o)))

GLFW_DEP_DIR := $(DEPS_DIR)/glfw
GLFW_BUILD_DIR := $(BUILD_DIR)/glfw
GLFW_LIB := $(GLFW_BUILD_DIR)/src/libglfw3.a

GLAD_DEP_DIR := $(DEPS_DIR)/glad
GLAD_OBJ := $(OBJS_DIR)/glad.o

CXX 		:= g++
CXXFLAGS	:= -Wall -Wextra -Werror -fPIC \
			   -I$(INCLUDE_DIR) \
			   -I$(GLAD_DEP_DIR)/include \
			   -I../include
LDFLAGS		:= -shared -ldl -lglfw

all: $(TARGET)

$(TARGET): $(GLFW_LIB) $(GLAD_OBJ) $(OBJS)
	@echo "→ Linking of $(TARGET)"
	$(CXX) $(OBJS) $(GLAD_OBJ) $(GLFW_LIB) $(LDFLAGS) -o $@

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "→ Compilation of $<"
	$(CXX) $(CXXFLAGS) $(DEFINE) -c $< -o $@

$(GLFW_DEP_DIR):
	@echo "→ Download of GLFW"
	@mkdir -p $(DEPS_DIR)
	git clone --depth=1 --branch 3.4 git@github.com:glfw/glfw.git $(DEPS_DIR)/glfw
$(GLFW_LIB): $(GLFW_DEP_DIR)
	@echo "→ Compilation of GLFW"
	@mkdir -p $(GLFW_BUILD_DIR)
	@cd $(GLFW_BUILD_DIR) && cmake -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF ../../$(DEPS_DIR)/glfw && make -s

$(GLAD_DEP_DIR):
	@echo "→ Download of GLAD generator"
	python3 -m venv .venv
	.venv/bin/pip install glad --quiet
	@echo "→ Generating GLAD files"
	.venv/bin/glad --profile core --api gl=4.6 --generator c --out-path $(GLAD_DEP_DIR)
$(GLAD_OBJ) : $(GLAD_DEP_DIR)
	@mkdir -p $(OBJS_DIR)
	@echo "→ Compilation of GLAD"
	$(CXX) $(CXXFLAGS) -I$(GLAD_DEP_DIR)/include -c $(GLAD_DEP_DIR)/src/glad.c -o $@


clean:
	rm -rf $(OBJS_DIR)

fclean:
	rm -rf $(DEPS_DIR)
	rm -rf $(BUILD_DIR)
	rm -rf .venv
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re

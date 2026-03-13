TARGET := lib_opengl.so

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
OBJS_DIR := $(BUILD_DIR)/objs
DEPS_DIR := lib

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
VPATH := $(dir $(SRCS))
OBJS := $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.cpp=.o)))

CXX 		:= g++
CXXFLAGS	:= -Wall -Wextra -Werror -fPIC \
			   -I$(INCLUDE_DIR) \
			   -I../include
LDFLAGS		:= -shared

GLFW_DEP_DIR := $(DEPS_DIR)/glfw
GLFW_BUILD_DIR := $(BUILD_DIR)/glfw
GLFW_LIB := $(GLFW_BUILD_DIR)/src/libglfw3.a

all: $(TARGET)

$(TARGET): $(GLFW_LIB) $(OBJS)
	@echo "→ Linking of $(TARGET)"
	$(CXX) $(OBJS) $(GLFW_LIB) $(LDFLAGS) -o $@

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
	@cd $(GLFW_BUILD_DIR) && cmake -DBUILD_SHARED_LIBS=OFF ../../$(DEPS_DIR)/glfw && make -s

clean:
	rm -rf $(OBJS_DIR)

fclean:
	rm -rf $(DEPS_DIR)
	rm -rf $(BUILD_DIR)
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re

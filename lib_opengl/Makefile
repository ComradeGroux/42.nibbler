BOLD  := \033[1m
GRAY  := \033[90m
GREEN := \033[32m
BLUE	:= \033[34m
RESET := \033[0m
ERASE := \r\033[2K

TARGET := lib_opengl.so

SRC_DIR     := src
INCLUDE_DIR := include
BUILD_DIR   := build
OBJS_DIR    := $(BUILD_DIR)/objs
DEPS_DIR    := lib

SRCS	:= $(wildcard $(SRC_DIR)/*.cpp)
VPATH	:= $(dir $(SRCS))
OBJS	:= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.cpp=.o)))

GLFW_VER		:= 3.4
GLFW_URL		:= https://github.com/glfw/glfw/archive/refs/tags/$(GLFW_VER).tar.gz
GLFW_DEP_DIR	:= $(DEPS_DIR)/glfw-$(GLFW_VER)
GLFW_BUILD_DIR	:= $(BUILD_DIR)/glfw
GLFW_LIB		:= $(GLFW_BUILD_DIR)/src/libglfw3.a

GLM_VER			:= 1.0.3
GLM_URL			:= https://github.com/g-truc/glm/archive/refs/tags/$(GLM_VER).tar.gz
GLM_DEP_DIR		:= $(DEPS_DIR)/glm-$(GLM_VER)

GLAD_DEP_DIR	:= $(DEPS_DIR)/glad
GLAD_OBJ		:= $(OBJS_DIR)/glad.o

CXX      := g++
CXXFLAGS := -Wall -Wextra -Werror -fPIC
INCLUDES := -I$(INCLUDE_DIR)           \
            -I$(GLM_DEP_DIR)           \
            -I$(GLAD_DEP_DIR)/include  \
            -I$(GLFW_DEP_DIR)/include  \
            -I../include
LDFLAGS  := -shared -ldl -lm -lGL -lX11 -lXrandr -lXi -Wl,--version-script=exports.map

all: $(TARGET)

$(TARGET): $(GLFW_LIB) $(GLAD_OBJ) $(OBJS)
	@printf "$(BOLD)Linking $(TARGET)$(RESET)\n"
	@$(CXX) $(OBJS) $(GLAD_OBJ) $(GLFW_LIB) $(LDFLAGS) -o $@
	@printf "$(GREEN)  ✓ $(TARGET) ready$(RESET)\n"



$(OBJS_DIR):
	@mkdir -p $@
$(OBJS): | $(GLFW_DEP_DIR) $(GLM_DEP_DIR) $(GLAD_DEP_DIR) $(OBJS_DIR)/.compile_start
$(OBJS_DIR)/.compile_start: $(SRCS)
	@printf "$(BOLD)Compiling$(RESET)\n"
	@touch $@
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	@printf "$(GRAY)  $<...$(RESET)" && \
	 $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ && \
	 printf "$(ERASE)$(GREEN)  ✓ $<$(RESET)\n"\



$(DEPS_DIR):
	@mkdir -p $@

$(GLFW_DEP_DIR): | $(DEPS_DIR)
	@printf "$(BOLD)Downloading GLFW $(GLFW_VER)$(RESET)\n"
	@printf "$(GRAY)  Fetching archive...$(RESET)" && \
	 curl -sL $(GLFW_URL) -o $(DEPS_DIR)/glfw.tar.gz && \
	 printf "$(ERASE)"
	@printf "$(GRAY)  Extracting...$(RESET)" && \
	 tar -xzf $(DEPS_DIR)/glfw.tar.gz -C $(DEPS_DIR) && \
	 printf "$(ERASE)"
	@rm $(DEPS_DIR)/glfw.tar.gz
	@printf "$(GREEN)  ✓ Done$(RESET)\n"
$(GLFW_LIB): $(GLFW_DEP_DIR) | $(OBJS_DIR)
	@printf "$(BOLD)Building GLFW $(GLFW_VER)$(RESET)\n"
	@mkdir -p $(GLFW_BUILD_DIR)
	@printf "$(GRAY)  Configuring cmake...$(RESET)" && \
	 cmake -S $(GLFW_DEP_DIR) -B $(GLFW_BUILD_DIR) \
	   -DBUILD_SHARED_LIBS=OFF                      \
	   -DGLFW_BUILD_EXAMPLES=OFF                    \
	   -DGLFW_BUILD_TESTS=OFF                       \
	   -DGLFW_BUILD_DOCS=OFF                        \
	   -DCMAKE_POSITION_INDEPENDENT_CODE=ON         \
	   -DCMAKE_BUILD_TYPE=Release                   \
	   > /dev/null 2>&1 && \
	 printf "$(ERASE)"
	@printf "$(GRAY)  Compiling...$(RESET)" && \
	 $(MAKE) -C $(GLFW_BUILD_DIR) -j$(shell nproc) --no-print-directory > /dev/null 2>&1 && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ Done$(RESET)\n"

$(GLM_DEP_DIR): | $(DEPS_DIR)
	@printf "$(BOLD)Downloading GLM $(GLM_VER)$(RESET)\n"
	@printf "$(GRAY)  Fetching archive...$(RESET)" && \
	 curl -sL $(GLM_URL) -o $(DEPS_DIR)/glm.tar.gz && \
	 printf "$(ERASE)"
	@printf "$(GRAY)  Extracting...$(RESET)" && \
	 tar -xzf $(DEPS_DIR)/glm.tar.gz -C $(DEPS_DIR) && \
	 printf "$(ERASE)"
	@rm $(DEPS_DIR)/glm.tar.gz
	@printf "$(GREEN)  ✓ Done$(RESET)\n"

$(GLAD_DEP_DIR): | $(DEPS_DIR)
	@printf "$(BOLD)Downloading GLAD (OpenGL 4.6 core)$(RESET)\n"
	@printf "$(GRAY)  Setting up virtual env...$(RESET)" && \
	 python3 -m venv $(DEPS_DIR)/.venv > /dev/null 2>&1 && \
	 printf "$(ERASE)"
	@printf "$(GRAY)  Installing glad...$(RESET)" && \
	 $(DEPS_DIR)/.venv/bin/pip install glad --quiet && \
	 printf "$(ERASE)"
	@printf "$(GRAY)  Generating sources...$(RESET)" && \
	 $(DEPS_DIR)/.venv/bin/glad --profile core --api gl=4.6 --generator c \
	   --out-path $(GLAD_DEP_DIR) > /dev/null 2>&1 && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ Done$(RESET)\n"
$(GLAD_OBJ): $(GLAD_DEP_DIR) | $(OBJS_DIR)
	@printf "$(BOLD)Compiling GLAD$(RESET)\n"
	@gcc -fPIC -I$(GLAD_DEP_DIR)/include -c $(GLAD_DEP_DIR)/src/glad.c -o $@
	@printf "$(GREEN)  ✓ Done$(RESET)\n"



clean:
	@printf "$(GRAY)  Removing build objects...$(RESET)" && \
	 rm -rf $(OBJS_DIR) && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ Build files cleaned$(RESET)\n"

fclean: clean
	@printf "$(GRAY)  Removing $(BUILD_DIR) and $(TARGET)...$(RESET)" && \
	 rm -rf $(BUILD_DIR) $(TARGET) && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ $(TARGET) cleaned$(RESET)\n"

dclean: fclean
	@printf "$(GRAY)  Removing $(DEPS_DIR)...$(RESET)" && \
	 rm -rf $(DEPS_DIR) && \
	 rm -rf .venv && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ Dependencies cleaned$(RESET)\n"

re: fclean all

.PHONY: all debug clean fclean dclean re
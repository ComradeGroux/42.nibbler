TARGET := nibbler

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
OBJS_DIR := $(BUILD_DIR)/objs

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

VPATH := $(dir $(SRCS))

OBJS := $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.cpp=.o)))

CLASS_DIRS := $(addprefix -I, $(addprefix $(SRC_DIR)/, $(CLASS_HEADERS)))

LIB_NCURSES_DIR	:= lib_ncurses
LIB_NCURSES		:= $(LIB_NCURSES_DIR)/lib_ncurses.so
LIB_OPENGL_DIR	:= lib_opengl
LIB_OPENGL 		:= $(LIB_OPENGL_DIR)/lib_opengl.so
LIB_VULKAN_DIR	:= lib_vulkan
LIB_VULKAN		:= $(LIB_VULKAN_DIR)/lib_vulkan.so

#########################
### COMPILATION RULES ###
#########################
CXX := g++
LDFLAGS := -rdynamic
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Werror \
			-I$(INCLUDE_DIR)
DEBUG_FLAGS := -g -DDEBUG

all: $(TARGET)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: all

$(TARGET): $(LIB_NCURSES) $(LIB_OPENGL) $(LIB_VULKAN) $(OBJS) 
	@echo "→ Linking of $(TARGET)"
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "→ Compilation of $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB_NCURSES):
	$(MAKE) -sC $(@D)

$(LIB_OPENGL):
	$(MAKE) -sC $(@D)

$(LIB_VULKAN):
	$(MAKE) -sC $(@D)


########################
#### CLEANING RULES ####
########################

libfclean:
	@echo "→ Cleaning lib_ncurses..."
	@$(MAKE) -sC $(LIB_NCURSES_DIR) fclean
	@echo "→ Cleaning lib_opengl..."
	@$(MAKE) -sC $(LIB_OPENGL_DIR) fclean
	@echo "→ Cleaning lib_vulkan..."
	@$(MAKE) -sC $(LIB_VULKAN_DIR) fclean

libclean:
	@echo "→ Cleaning lib_ncurses objects..."
	@$(MAKE) -sC $(LIB_NCURSES_DIR) clean
	@echo "→ Cleaning lib_opengl objects...."
	@$(MAKE) -sC $(LIB_OPENGL_DIR) clean
	@echo "→ Cleaning lib_vulkan objects..."
	@$(MAKE) -sC $(LIB_VULKAN_DIR) clean

clean: libclean
	@echo "→ Cleaning objects..."
	@rm -rf $(OBJS_DIR)

fclean: libfclean
	@echo "→ Cleaning in depths..."
	@rm -rf $(BUILD_DIR)
	@rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re

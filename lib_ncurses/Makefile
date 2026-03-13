TARGET := lib_ncurses.so

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
LDFLAGS		:= -shared -fPIC -lncurses

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "→ Linking of $(TARGET)"
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "→ Compilation of $<"
	$(CXX) $(CXXFLAGS) $(DEFINE) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean:
	rm -rf $(DEPS_DIR)
	rm -rf $(BUILD_DIR)
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re

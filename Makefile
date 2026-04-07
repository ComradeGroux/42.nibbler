BOLD	:= \033[1m
GRAY	:= \033[90m
GREEN	:= \033[32m
BLUE	:= \033[34m
RESET	:= \033[0m
ERASE	:= \r\033[2K

TARGET	:= nibbler

SRC_DIR		:= src
INCLUDE_DIR := include
BUILD_DIR	:= build
OBJS_DIR	:= $(BUILD_DIR)/objs
DEPS_DIR	:=
LIB_SEP		:= $(BUILD_DIR)/.lib_sep

SRCS	:= $(wildcard $(SRC_DIR)/*.cpp)
VPATH	:= $(dir $(SRCS))
OBJS	:= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.cpp=.o)))

LIB1_DIR	:= lib_ncurses
LIB1		:= $(LIB1_DIR)/$(LIB1_DIR).so
LIB2_DIR	:= lib_opengl
LIB2 		:= $(LIB2_DIR)/$(LIB2_DIR).so
LIB3_DIR	:= lib_vulkan
LIB3		:= $(LIB3_DIR)/$(LIB3_DIR).so


CXX 		:= g++
LDFLAGS 	:= -rdynamic
CXXFLAGS 	:= -std=c++17 -O2 -Wall -Wextra -Werror
INCLUDES	:= -I$(INCLUDE_DIR)

all: $(TARGET)

$(TARGET): $(LIB1) $(LIB2) $(LIB3) $(OBJS)
	@printf "$(BOLD)Linking $(TARGET)$(RESET)\n"
	@$(CXX) $(OBJS) $(GLAD_OBJ) $(GLFW_LIB) $(LDFLAGS) -o $@
	@printf "$(GREEN)  ✓ $(TARGET) ready$(RESET)\n"
	@rm -f $(LIB_SEP)



$(OBJS_DIR):
	@mkdir -p $@
$(OBJS): | $(OBJS_DIR)/.compile_start
$(OBJS_DIR)/.nibbler_start: $(LIB1) $(LIB2) $(LIB3) $(SRCS) | $(OBJS_DIR)
	@test -f $(LIB_SEP) && printf "\n" || mkdir -p $(BUILD_DIR); touch $(LIB_SEP)
	@printf "$(BOLD)$(BLUE)Compiling $(TARGET)$(RESET)\n"
	@touch $@
$(OBJS_DIR)/.compile_start: $(SRCS) | $(OBJS_DIR)/.nibbler_start
	@printf "$(BOLD)Compiling$(RESET)\n"
	@touch $@
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	@printf "$(GRAY)  $<...$(RESET)" && \
	 $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ && \
	 printf "$(ERASE)$(GREEN)  ✓ $<$(RESET)\n"\



$(LIB1):
	@test -f $(LIB_SEP) && printf "\n" || mkdir -p $(BUILD_DIR); touch $(LIB_SEP)
	@printf "$(BOLD)$(BLUE)Compiling $(LIB1_DIR)$(RESET)\n"
	@$(MAKE) -sC $(@D)

$(LIB2):
	@test -f $(LIB_SEP) && printf "\n" || mkdir -p $(BUILD_DIR); touch $(LIB_SEP)
	@printf "$(BOLD)$(BLUE)Compiling $(LIB2_DIR)$(RESET)\n"
	@$(MAKE) -sC $(@D)

$(LIB3):
	@test -f $(LIB_SEP) && printf "\n" || mkdir -p $(BUILD_DIR); touch $(LIB_SEP)
	@printf "$(BOLD)$(BLUE)Compiling $(LIB3_DIR)$(RESET)\n"
	@$(MAKE) -sC $(@D)


clean:
	@printf "$(BOLD)$(BLUE)Cleaning $(LIB1_DIR)...$(RESET)\n"
	@$(MAKE) -sC $(LIB1_DIR) clean
	@printf "$(BOLD)$(BLUE)Cleaning $(LIB2_DIR)...$(RESET)\n"
	@$(MAKE) -sC $(LIB2_DIR) clean
	@printf "$(BOLD)$(BLUE)Cleaning $(LIB3_DIR)...$(RESET)\n"
	@$(MAKE) -sC $(LIB3_DIR) clean

	@printf "$(BOLD)$(BLUE)Cleaning $(TARGET) objects...$(RESET)\n"
	@printf "$(GRAY)  Removing build objects...$(RESET)" && \
	 rm -rf $(OBJS_DIR) && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ Build files cleaned$(RESET)\n"

fclean:
	@printf "$(BOLD)$(BLUE)Cleaning $(LIB1_DIR)...$(RESET)\n"
	@$(MAKE) -sC $(LIB1_DIR) fclean
	@printf "$(BOLD)$(BLUE)Cleaning $(LIB2_DIR)...$(RESET)\n"
	@$(MAKE) -sC $(LIB2_DIR) fclean
	@printf "$(BOLD)$(BLUE)Cleaning $(LIB3_DIR)...$(RESET)\n"
	@$(MAKE) -sC $(LIB3_DIR) fclean

	@printf "$(BOLD)$(BLUE)Cleaning $(TARGET)...$(RESET)\n"
	@printf "$(GRAY)  Removing $(BUILD_DIR)...$(RESET)" && \
	 rm -rf $(BUILD_DIR) && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ Build files cleaned$(RESET)\n"
	@printf "$(GRAY)  Removing $(TARGET)...$(RESET)" && \
	 rm -rf $(TARGET) && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ $(TARGET) cleaned$(RESET)\n"

dclean:
	@printf "$(BOLD)$(BLUE)Cleaning $(LIB1_DIR)...$(RESET)\n"
	@$(MAKE) -sC $(LIB1_DIR) dclean
	@printf "$(BOLD)$(BLUE)Cleaning $(LIB2_DIR)...$(RESET)\n"
	@$(MAKE) -sC $(LIB2_DIR) dclean
	@printf "$(BOLD)$(BLUE)Cleaning $(LIB3_DIR)...$(RESET)\n"
	@$(MAKE) -sC $(LIB3_DIR) dclean

	@printf "$(BOLD)$(BLUE)Cleaning $(TARGET)...$(RESET)\n"
	@printf "$(GRAY)  Removing $(BUILD_DIR)...$(RESET)" && \
	 rm -rf $(BUILD_DIR) && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ Build files cleaned$(RESET)\n"
	@printf "$(GRAY)  Removing $(TARGET)...$(RESET)" && \
	 rm -rf $(TARGET) && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ $(TARGET) cleaned$(RESET)\n"
	@printf "$(GRAY)  Removing $(DEPS_DIR)...$(RESET)" && \
	 rm -rf $(DEPS_DIR) && \
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ Dependencies cleaned$(RESET)\n"

seperate:
	@printf	"\n"
re: fclean seperate all

.PHONY: all clean fclean dclean re

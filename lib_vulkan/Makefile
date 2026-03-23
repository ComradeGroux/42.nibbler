BOLD  := \033[1m
GRAY  := \033[90m
GREEN := \033[32m
BLUE	:= \033[34m
RESET := \033[0m
ERASE := \r\033[2K

TARGET := lib_vulkan.so

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
OBJS_DIR := $(BUILD_DIR)/objs
DEPS_DIR := lib

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
VPATH := $(dir $(SRCS))
OBJS := $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.cpp=.o)))

VOLK_VER    := 1.3.295
VOLK_URL    := https://github.com/zeux/volk/archive/refs/tags/$(VOLK_VER).tar.gz
VOLK_DEP_DIR := $(DEPS_DIR)/volk-$(VOLK_VER)

GLM_VER		:= 1.0.3
GLM_URL		:= https://github.com/g-truc/glm/archive/refs/tags/$(GLM_VER).tar.gz
GLM_DEP_DIR	:= $(DEPS_DIR)/glm-$(GLM_VER)

SDL_VER			:= 3.4.2
SDL_URL			:= https://github.com/libsdl-org/SDL/archive/refs/tags/release-$(SDL_VER).tar.gz
SDL_DEP_DIR		:= $(DEPS_DIR)/sdl-$(SDL_VER)
SDL_BUILD_DIR	:= $(BUILD_DIR)/sdl
SDL_LIB			:= $(SDL_BUILD_DIR)/libSDL3.a

CXX 		:= g++
CXXFLAGS	:= -Wall -Wextra -Werror -fPIC
INCLUDES	:= -I$(INCLUDE_DIR) \
			   -I$(GLM_DEP_DIR) \
			   -I$(SDL_DEP_DIR)/include \
			   -I$(VOLK_DEP_DIR) \
			   -I../include
LDFLAGS		:= -shared -lm -ldl -lpthread -lwayland-client -lwayland-egl -lwayland-cursor -lxkbcommon -Wl,--version-script=exports.map

all: $(TARGET)

$(TARGET): $(SDL_LIB) $(OBJS)
	@printf "$(BOLD)Linking $(TARGET)$(RESET)\n"
	@$(CXX) $(OBJS) $(SDL_LIB) $(LDFLAGS) -o $@
	@printf "$(GREEN)  ✓ $(TARGET) ready$(RESET)\n"



$(OBJS_DIR):
	@mkdir -p $@
$(OBJS): | $(VOLK_DEP_DIR) $(GLM_DEP_DIR) $(SDL_DEP_DIR) $(OBJS_DIR)/.compile_start
$(OBJS_DIR)/.compile_start: $(SRCS)
	@printf "$(BOLD)Compiling$(RESET)\n"
	@touch $@
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	@printf "$(GRAY)  $<...$(RESET)" && \
	 $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ && \
	 printf "$(ERASE)$(GREEN)  ✓ $<$(RESET)\n"\



$(DEPS_DIR):
	@mkdir -p $@

$(VOLK_DEP_DIR): | $(DEPS_DIR)
	@printf "$(BOLD)Downloading VOLK $(VOLK_VER)$(RESET)\n"
	@printf "$(GRAY)  Fetching archive...$(RESET)" && \
	 curl -sL $(VOLK_URL) -o $(DEPS_DIR)/volk.tar.gz && \
	 printf "$(ERASE)"
	@printf "$(GRAY)  Extracting...$(RESET)" && \
	 tar -xzf $(DEPS_DIR)/volk.tar.gz -C $(DEPS_DIR) && \
	 printf "$(ERASE)"
	@rm $(DEPS_DIR)/volk.tar.gz
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

$(SDL_DEP_DIR): | $(DEPS_DIR)
	@printf "$(BOLD)Downloading SDL $(SDL_VER)$(RESET)\n"
	@printf "$(GRAY)  Fetching archive...$(RESET)" && \
	 curl -sL $(SDL_URL) -o $(DEPS_DIR)/sdl.tar.gz && \
	 printf "$(ERASE)"
	@mkdir -p $(SDL_DEP_DIR)
	@printf "$(GRAY)  Extracting...$(RESET)" && \
	 tar -xzf $(DEPS_DIR)/sdl.tar.gz -C $(SDL_DEP_DIR) --strip-components=1 && \
	 printf "$(ERASE)"
	@rm $(DEPS_DIR)/sdl.tar.gz
	@printf "$(GREEN)  ✓ Done$(RESET)\n"
$(SDL_LIB) : $(SDL_DEP_DIR) | $(OBJS_DIR)
	@printf "$(BOLD)Building SDL $(SDL_VER)$(RESET)\n"
	@mkdir -p $(SDL_BUILD_DIR)
	@printf "$(GRAY)  Configuring cmake...$(RESET)" && \
	 cmake -S $(SDL_DEP_DIR) -B $(SDL_BUILD_DIR) \
		-DSDL_STATIC=ON                     \
		-DSDL_SHARED=OFF                    \
		-DSDL_DEPS_SHARED=OFF               \
		-DSDL_VIDEO=ON                      \
		-DSDL_EVENTS=ON                     \
		-DSDL_VULKAN=ON                     \
		-DSDL_TIMERS=ON                     \
		-DSDL_PTHREADS=ON                   \
		-DSDL_PTHREADS_SEM=ON               \
		-DSDL_GCC_ATOMICS=ON                \
		-DSDL_LIBC=ON                       \
		-DSDL_CLOCK_GETTIME=ON              \
		-DSDL_WAYLAND=ON                    \
		-DSDL_WAYLAND_SHARED=OFF            \
		-DSDL_WAYLAND_LIBDECOR=OFF          \
		-DSDL_WAYLAND_LIBDECOR_SHARED=OFF   \
		-DSDL_X11=OFF                       \
		-DSDL_AUDIO=OFF                     \
		-DSDL_ALSA=OFF                      \
		-DSDL_ALSA_SHARED=OFF               \
		-DSDL_JACK=OFF                      \
		-DSDL_JACK_SHARED=OFF               \
		-DSDL_PIPEWIRE=OFF                  \
		-DSDL_PIPEWIRE_SHARED=OFF           \
		-DSDL_PULSEAUDIO=OFF                \
		-DSDL_PULSEAUDIO_SHARED=OFF         \
		-DSDL_SNDIO=OFF                     \
		-DSDL_SNDIO_SHARED=OFF              \
		-DSDL_DISKAUDIO=OFF                 \
		-DSDL_DUMMYAUDIO=OFF                \
		-DSDL_CAMERA=OFF                    \
		-DSDL_DUMMYCAMERA=OFF               \
		-DSDL_RENDER=OFF                    \
		-DSDL_RENDER_GPU=OFF                \
		-DSDL_RENDER_VULKAN=OFF             \
		-DSDL_GPU=OFF                       \
		-DSDL_OPENGL=OFF                    \
		-DSDL_OPENGLES=OFF                  \
		-DSDL_OFFSCREEN=OFF                 \
		-DSDL_DUMMYVIDEO=OFF                \
		-DSDL_KMSDRM=OFF                    \
		-DSDL_KMSDRM_SHARED=OFF             \
		-DSDL_JOYSTICK=OFF                  \
		-DSDL_HIDAPI=OFF                    \
		-DSDL_HIDAPI_JOYSTICK=OFF           \
		-DSDL_HIDAPI_LIBUSB=OFF             \
		-DSDL_HIDAPI_LIBUSB_SHARED=OFF      \
		-DSDL_VIRTUAL_JOYSTICK=OFF          \
		-DSDL_HAPTIC=OFF                    \
		-DSDL_SENSOR=OFF                    \
		-DSDL_POWER=OFF                     \
		-DSDL_DIALOG=OFF                    \
		-DSDL_TRAY=OFF                      \
		-DSDL_DBUS=OFF                      \
		-DSDL_IBUS=OFF                      \
		-DSDL_LIBURING=OFF                  \
		-DSDL_LIBUDEV=OFF                   \
		-DSDL_FRIBIDI=OFF                   \
		-DSDL_FRIBIDI_SHARED=OFF            \
		-DSDL_LIBTHAI=OFF                   \
		-DSDL_LIBTHAI_SHARED=OFF            \
		-DSDL_ASSEMBLY=OFF                  \
		-DSDL_INSTALL=OFF                   \
		-DSDL_INSTALL_CPACK=OFF             \
		-DSDL_UNINSTALL=OFF                 \
		-DSDL_TESTS=OFF                     \
		-DSDL_TEST_LIBRARY=OFF              \
		-DSDL_EXAMPLES=OFF                  \
		-DSDL_ASAN=OFF                      \
		-DSDL_WERROR=OFF                    \
		-DSDL_CCACHE=OFF                    \
		-DSDL_CLANG_TIDY=OFF                \
		-DSDL_DLOPEN_NOTES=OFF              \
		-DSDL_RPATH=OFF						\
		-DCMAKE_POSITION_INDEPENDENT_CODE=ON\
		-DCMAKE_BUILD_TYPE=Release 			\
	 > /dev/null 2>&1 && \
	 printf "$(ERASE)"
	@printf "$(GRAY)  Compiling...$(RESET)" && \
	 $(MAKE) -C $(SDL_BUILD_DIR) -j$(shell nproc) --no-print-directory > /dev/null 2>&1 && \
	 printf "$(ERASE)"
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
	 printf "$(ERASE)"
	@printf "$(GREEN)  ✓ Dependencies cleaned$(RESET)\n"

re: fclean all

.PHONY: all clean fclean dclean re

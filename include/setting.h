#pragma once

#include "ANSI-color-codes.h"

#define NUMBER_OPTIONS 3
#define WIDTH	0
#define HEIGHT	1
#define LIB		2

#define MIN_WIDTH 480
#define MAX_WIDTH 720

#define MIN_HEIGHT 480
#define MAX_HEIGHT 720

#define LIB1 "ncurses"
#define LIB1_PATH "lib_" LIB1 "/lib_" LIB1 ".so"

#define LIB2 "opengl"
#define LIB2_PATH "lib_" LIB2 "/lib_" LIB2 ".so"

#define LIB3 "vulkan"
#define LIB3_PATH "lib_" LIB3 "/lib_" LIB3 ".so"

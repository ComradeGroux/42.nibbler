#include <dlfcn.h>

#include <iostream>
#include "ANSI-color-codes.h"

#include <string.h>

#define NUMBER_OPTIONS 3
#define WIDTH	0
#define HEIGHT	1
#define LIB		2

inline static void	printUsage(void)
{
	std::cout << BYEL << "[USAGE]" << CRESET << " nibbler -w <WIDTH> -h <HEIGHT>" << std::endl;
}

static void	printHelp(void)
{
	std::cout << "An application to learn dynamic libraries" << std::endl << std::endl;
	std::cout << BWHT << "USAGE:" << CRESET << " nibbler" << CRESET << " --width <WIDTH> --height <HEIGHT> [OPTIONS]" << std::endl << std::endl;
	std::cout << BWHT << "MANDATORY FLAGS:" << CRESET << std::endl;
	std::cout << "  -w <WIDTH>,  --width <WIDTH>                   Width of the window in pixels" << std::endl;
	std::cout << "  -h <HEIGHT>, --height <HEIGHT>                 Height of the window in pixels" << std::endl << std::endl;
	std::cout << BWHT << "OPTIONNAL FLAGS:" << CRESET << std::endl;
	std::cout << "               --lib [" << UWHT << "ncurses" << CRESET << ", opengl, vulkan]   Library to use at launched" << std::endl;
	std::cout << "               --help                            Print this help message" << std::endl;
}

static void	freeOptions(char **options)
{
	for (unsigned int i = 0; i < NUMBER_OPTIONS; i++)
	{
		if (options[i] != NULL)
			free(options[i]);
	}
}

static int	parseArguments(int argc, char **argv, char **options)
{
	if (argc < 2)
	{
		std::cerr << BRED << "[ERROR]" << CRESET << " Wrong number of arguments" << std::endl;
		printUsage();
		return -1;
	}

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--help") == 0)
		{
			printHelp();
			return 1;
		}
		else if ((strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) && argv[i + 1] && argv[i + 1][0] != '-')
			options[WIDTH] = strdup(argv[++i]);
		else if ((strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0) && argv[i + 1] && argv[i + 1][0] != '-')
			options[HEIGHT] = strdup(argv[++i]);
		else if (strcmp(argv[i], "-lib") == 0 && argv[i + 1] && argv[i + 1][0] != '-')
			options[LIB] = strdup(argv[++i]);
		else
		{
			std::cerr << BRED << "[ERROR]" << CRESET << " Invalid arguments name or missing value" << std::endl;
			printUsage();
			return -1;
		}
	}

	if (options[WIDTH] == NULL)
	{
		std::cerr << BRED << "[ERROR]" << CRESET << " -w must be specified" << std::endl;
		printUsage();
		return -1;
	}
	else if (options[HEIGHT] == NULL)
	{
		std::cerr << BRED << "[ERROR]" << CRESET << " -h must be specified" << std::endl;
		printUsage();
		return -1;
	}
	else if (options[LIB] == NULL)
		options[LIB] = strdup("ncurses");

	return 0;
}

int	main(int argc, char** argv)
{
	char	*options[NUMBER_OPTIONS] = { NULL };
	if (parseArguments(argc, argv, options) == -1)
	{
		freeOptions(options);
		return EXIT_FAILURE;
	}

	freeOptions(options);
	return EXIT_SUCCESS;
}

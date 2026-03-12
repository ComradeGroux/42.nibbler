#include <dlfcn.h>

#include <iostream>
#include <string.h>

#include "setting.h"

inline static void	printUsage(void)
{
	std::cout << BYEL << "[USAGE]" << CRESET << " nibbler -w <WIDTH> -h <HEIGHT>" << std::endl;
}

inline static void	printHelp(void)
{
	std::cout << "An application to learn dynamic libraries" << std::endl << std::endl;
	std::cout << BWHT << "USAGE:" << CRESET << " nibbler" << CRESET << " --width <WIDTH> --height <HEIGHT> [OPTIONS]" << std::endl << std::endl;
	std::cout << BWHT << "MANDATORY FLAGS:" << CRESET << std::endl;
	std::cout << "  -w <WIDTH>,  --width <WIDTH>                   Width of the window in pixels. Must be between " << BWHT << MIN_WIDTH << CRESET << " and " << BWHT << MAX_WIDTH << CRESET << std::endl;
	std::cout << "  -h <HEIGHT>, --height <HEIGHT>                 Height of the window in pixels. Must be between " << BWHT << MIN_HEIGHT << CRESET << " and " << BWHT << MAX_HEIGHT << CRESET<< std::endl << std::endl;
	std::cout << BWHT << "OPTIONNAL FLAGS:" << CRESET << std::endl;
	std::cout << "  -l,          --lib [" << UWHT << LIB1 << CRESET << ", " << LIB2 << ", " << LIB3 << "]   Library to use at launched" << std::endl;
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
			freeOptions(options);
			exit(EXIT_SUCCESS);
		}
		else if ((strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) && argv[i + 1] && argv[i + 1][0] != '-')
			options[WIDTH] = strdup(argv[++i]);
		else if ((strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0) && argv[i + 1] && argv[i + 1][0] != '-')
			options[HEIGHT] = strdup(argv[++i]);
		else if ((strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lib") == 0) && argv[i + 1] && argv[i + 1][0] != '-')
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
		options[LIB] = strdup(LIB1);

	return 0;
}

static int	processArguments(char **options, int &width, int &height)
{
	width = std::atoi(options[WIDTH]);
	height = std::atoi(options[HEIGHT]);

	if (width < MIN_WIDTH || width > MAX_WIDTH)
	{
		std::cerr << BRED << "[ERROR]" << CRESET << " Wrong width value, must be included between " <<
					 BWHT << MIN_WIDTH << CRESET << " and " << BWHT << MAX_WIDTH << CRESET << std::endl;
		return -1;
	}
	if (height < MIN_HEIGHT || height > MAX_HEIGHT)
	{
		std::cerr << BRED << "[ERROR]" << CRESET << " Wrong height value, must be included between " <<
					 BWHT << MIN_HEIGHT << CRESET << " and " << BWHT << MAX_HEIGHT << CRESET << std::endl;
		return -1;
	}

	if (strcmp(options[LIB], LIB1) != 0 && strcmp(options[LIB], LIB2) != 0 && strcmp(options[LIB], LIB3) != 0)
	{
		std::cerr << BRED << "[ERROR]" << CRESET << " The selectionned library is not supported. Available choices: " <<
					 BWHT << LIB1 << CRESET << ", " << BWHT << LIB2 << CRESET << " or " << BWHT << LIB3 << CRESET << std::endl;
		return -1;
	}

	return 0;
}

int	main(int argc, char** argv)
{
	char	*options[NUMBER_OPTIONS] = { NULL };
	int	width = 0;
	int	height = 0;

	if (parseArguments(argc, argv, options) == -1 || processArguments(options, width, height) == -1)
	{
		freeOptions(options);
		return EXIT_FAILURE;
	}

	freeOptions(options);
	return EXIT_SUCCESS;
}

#include "LibLoader.hpp"

#include "setting.h"

#include <stdexcept>
#include <string.h>
#include <string>
#include <dlfcn.h>

LibLoader::LibLoader(void)
{
	_handle = nullptr;
	_lib = nullptr;
}

LibLoader::LibLoader(const LibLoader &src)
{
	_handle = src._handle;
	_lib = src._lib;
}

LibLoader	LibLoader::operator=(const LibLoader &src)
{
	_handle = src._handle;
	_lib = src._lib;

	return *this;
}

LibLoader::~LibLoader(void)
{
	unload();
}

void	LibLoader::load(const char *lib_name)
{
	if (strcmp(lib_name, LIB1) == 0)
		_loadLib(LIB1_PATH);
	else if (strcmp(lib_name, LIB2) == 0)
		_loadLib(LIB2_PATH);
	else if (strcmp(lib_name, LIB3) == 0)
		_loadLib(LIB3_PATH);
}

void	LibLoader::_loadLib(const char *path)
{
	if (_handle)
		unload();

	_handle = dlopen(path, RTLD_LAZY);
	if (_handle == NULL)
		throw std::runtime_error("Library not found");

	const char* err = dlerror();
	if (err)
		throw std::runtime_error(err);

	using CreateFunc = IGraphLib*(*)();
	CreateFunc create = (CreateFunc)dlsym(_handle, "create");

	err = dlerror();
	if (err)
		throw std::runtime_error(err);

	_lib = create();
}

void	LibLoader::unload(void)
{
	if (_lib)
	{
		using DestroyFunc = void(*)(IGraphLib*);
		DestroyFunc destroy = (DestroyFunc)dlsym(_handle, "destroy");
		if (destroy)
			destroy(_lib);
		_lib = nullptr;
	}

	if (_handle)
	{
		dlclose(_handle);
		_handle = nullptr;
	}
}

IGraphLib*	LibLoader::get(void) const
{
	return _lib;
}

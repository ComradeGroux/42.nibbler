#include "LibLoader.hpp"

#include "setting.h"

#include <stdexcept>
#include <string.h>
#include <string>
#include <dlfcn.h>

LibLoader::LibLoader(void) : _handle(nullptr), _lib(nullptr)
{
}

LibLoader::LibLoader(const LibLoader &src) : _handle(nullptr), _lib(nullptr)
{
	if (!src._lib_name.empty())
		load(src._lib_name.c_str());
}

LibLoader&	LibLoader::operator=(const LibLoader &src)
{
	if (this == &src)
		return *this;

	unload();
	if (!src._lib_name.empty())
		load(src._lib_name.c_str());

	return *this;
}

LibLoader::~LibLoader(void)
{
	unload();
}

void	LibLoader::load(const char *lib_name)
{
	if (!_lib_name.empty() && strcmp(_lib_name.c_str(), lib_name) == 0)
		return ;

	_lib_name.assign(lib_name);

	if (strcmp(lib_name, LIB1) == 0)
		_loadLib(LIB1_PATH);
	else if (strcmp(lib_name, LIB2) == 0)
		_loadLib(LIB2_PATH);
	else if (strcmp(lib_name, LIB3) == 0)
		_loadLib(LIB3_PATH);
	else
		throw BadLibraryException();
}

void	LibLoader::_loadLib(const char *path)
{
	if (_handle)
		unload();

	_handle = dlopen(path, RTLD_LAZY);
	if (_handle == NULL)
		throw LibraryNotFoundException();

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

const char*	LibLoader::BadLibraryException::what() const throw()
{
	return "Bad library";
}

const char*	LibLoader::LibraryNotFoundException::what() const throw()
{
	return "Library not found";
}

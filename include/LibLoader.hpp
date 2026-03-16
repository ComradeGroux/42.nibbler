#pragma once

#include "IGraphLib.hpp"
#include <exception>
#include <string>

class	LibLoader {
	private:
		void		*_handle;
		IGraphLib	*_lib;

		std::string	_lib_name;

		void	_loadLib(const char *path);

	public:
		LibLoader(void);
		LibLoader(const LibLoader &src);
		LibLoader&	operator=(const LibLoader &src);
		~LibLoader(void);

		void		load(const char *lib_name);
		void		unload(void);
	
		IGraphLib*	get(void) const;

		class	BadLibraryException : public std::exception {
			public:
				virtual const char*	what(void) const throw();
		};
		class	LibraryNotFoundException : public std::exception {
			public:
				virtual const char*	what(void) const throw();
		};
};

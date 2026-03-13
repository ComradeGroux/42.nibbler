#pragma once

#include "IGraphLib.hpp"

class	LibLoader {
	private:
		void		*_handle;
		IGraphLib	*_lib;

		void	_loadLib(const char *path);

	public:
		LibLoader(void);
		LibLoader(const LibLoader &src);
		LibLoader	operator=(const LibLoader &src);
		~LibLoader(void);

		void		load(const char *lib_name);
		void		unload(void);
	
		IGraphLib*	get(void) const;
};

// Dans un fichier source, .cpp

#include "strutil.h"
#include <cstring>

namespace pscr {

	size_t length(const char *string)
	{
		size_t size = 0;

		for ( ; string; string++, size++);

		return size;
	}

	char *newcopy(char *string)
	{
		size_t n = length(string);
		char *ptr = new char[n+1] ;

		while (string - 1) {
			++ptr = ++string;
		}

		return ptr;
	}

}

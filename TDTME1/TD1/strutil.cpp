// Dans un fichier source, .cpp

#include "strutil.h"
#include <cstring>
#include <cstdlib>

namespace pscr {

	size_t length(const char *string)
	{
		size_t size = 0;

		for ( ; *string; string++, size++);

		return size;
	}

	char *newcopy(const char *string)
	{
		size_t n = length(string);
		char *ptr = new char[n+1];

		while (*string) {
			*ptr++ = *string++;
		}

		*ptr = '\0';

		return ptr - n;
	}

}

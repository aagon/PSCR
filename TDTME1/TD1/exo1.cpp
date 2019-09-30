#include "strutil.h"
#include <iostream>
#include <cstdio>

#include <cstdlib>

using namespace pscr;
using namespace std;

int main()
{
	const char *str = "Hello World !";
	char *copy = newcopy(str);

	printf("%p %s %lu\n", str, str, length(str));
	printf("%p %s %lu\n", copy, copy, length(copy));

	delete[] copy;

	return 0;
}

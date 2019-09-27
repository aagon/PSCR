#include "strutil.h"
#include <iostream>

using namespace pscr;
using namespace std;

int main()
{
	char *str = "Hello World !";
	char *copy = newcopy(str);

	std::cout << str << (*str) << length(str) << std::endl;
	cout << copy << (*copy) << length(copy) << endl;

	delete[] copy;

	return 0;
}

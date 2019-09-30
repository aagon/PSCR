#include "string.h"
#include "strutil.h"
#include <iostream>

using namespace std;

namespace pscr {

	String::String(const char *ori):str(ori)
	{}

	size_t String::length() const
	{
		return pscr::length(str);
	}

	ostream & operator<< (ostream &os, const pscr::String &s)
	{
		return os << s.str;
	}
}

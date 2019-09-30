#pragma once

#include <cstring>
#include <iostream>

namespace pscr {

	class String {
		friend std::ostream & operator<< (ostream &os, const pscr::String &str);
		const char *str;
	public:
		String(const char* ori);
		size_t length() const;
	};

	std::ostream & operator<< (ostream &os, const pscr::String &str);
}

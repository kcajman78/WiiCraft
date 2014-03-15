// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>

class Convert
{
public:
	template <typename T>
	static std::string T_to_string(T const &val)
	{
		std::ostringstream ostr;
		ostr << val;

		return ostr.str();
	}

	template <typename T>
	static T string_to_T(std::string const &val)
	{
		std::istringstream istr(val);
		T returnVal;
			
		return returnVal;
	}

	//template <>
	static std::string string_to_T(std::string const &val)
	{
		return val;
	}
};

#endif
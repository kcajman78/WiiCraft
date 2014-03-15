// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline


#ifndef _MAINAPI_HPP_
#define _MAINAPI_HPP_

#define APIVERISON "01"
#define APILANGUE "LUA"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <stdio.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <zlib.h>
//#include "worldAPI.h"
//#include "blockAPI"
//#include "playerAPI.h"
//#include "multiplayerAPI.h"
//#include "mobAPI.h"


using namespace std;

class API {
	private:
		bool APIRunning;
		bool APIVERISONBool;
		
	public:
		API();
		~API();
		void initAPI(void);
		void stopAPI();
		
		//Public valuse:
		bool existsAPI;
		bool existsTEXTURES;
		bool existsLUA;
		string LUAPATH;
};



#endif
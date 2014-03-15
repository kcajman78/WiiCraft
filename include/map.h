// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#ifndef _MAP_H_
#define _MAP_H_

#include "ChunkHandler.hpp"

#define Xmap 32
#define Ymap 32
#define Zmap 32
#define groundLevel 0
#define groundID 1

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <stdio.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <fat.h>
//#include <zlib.h>
#include <vector>

using namespace std;

class MAP {
	private:
		bool mapFromFile;
		
		
	public:
		MAP();
		~MAP();
		void loadMap();
		void createMapArray();
		void generateMap();
		void closeMap();
		void updateMap();
		void saveMap();
		
		//Public valuse:
		string mapPath;
		double mapArray[Zmap][Ymap][Xmap];
};

//extern MAP mainMAP;

/*static int seeGeneratedMapBlock(int z, int y, int x){
	if(mainMAP.mapArray[z][y][x] == true){
		return mainMAP.mapArray[z][y][x];
	} //else
	return false;
}*/

#endif
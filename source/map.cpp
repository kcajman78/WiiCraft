// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

/*

	(c)Filiph Sandström

									*/
//mapArray[Z][Y][X] = blockID <-- Good to know =) -filfat

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
#include <sstream>
#include <sys/stat.h>
#include <vector>

#include "map.h"
#include "utils.h"
#include "debug.h"

using namespace std;

MAP::MAP(){
	Debug("Map() Started");
	createMapArray();
	Debug("Done With createMapArray();");
	generateMap();
	Debug("Done With generateMap();");
	Debug("Map() Ended");
}

MAP::~MAP(){
	closeMap();
}

void MAP::loadMap() {
	
}

void MAP::saveMap() {
	
}

void MAP::updateMap() {
	
}

void MAP::createMapArray() {

  // Allocate memory
  /*mapArray = new double**[Xmap];
  for (int i = 0; i < Xmap; ++i) {
    mapArray[i] = new double*[Ymap];

    for (int j = 0; j < Ymap; ++j)
      mapArray[i][j] = new double[Zmap];
  }*/
}

void MAP::generateMap(){
	// Makes a Flat Map
	for(int tempX = 0; tempX <= Xmap; ++tempX){
		for(int tempY = 0; tempY <= Xmap; ++tempY){
			mapArray[groundLevel][tempY][tempX] = groundID;
		}
	}
	
}

void MAP::closeMap(){
  /*// De-Allocate memory to prevent memory leak
  for (int i = 0; i < Xmap; ++i) {
    for (int j = 0; j < Ymap; ++j)
      delete [] mapArray[i][j];

    delete [] mapArray[i];
  }
  delete [] mapArray;*/
}
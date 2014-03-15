// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#ifndef _WIICRAFT_HPP_
#define _WIICRAFT_HPP_

//World stuff
	#define WORLD_SIZE				4
	#define WORLD_AREA				WORLD_SIZE * WORLD_SIZE
	#define WORLD_VOLUME			WORLD_AREA * WORLD_SIZE
	#define WORLD_TOTAL_SIZE		WORLD_SIZE * CHUNK_TOTAL_SIZE
	#define getWorldIndex(x,y,z) 	((x) + (y) * WORLD_SIZE + (z) * WORLD_AREA)
	
//Chunk stuff
	#define CHUNK_SIZE				8
	#define CHUNK_AREA				CHUNK_SIZE * CHUNK_SIZE
	#define CHUNK_VOLUME			CHUNK_SIZE_AREA  * CHUNK_SIZE
	#define CHUNK_TOTAL_SIZE		CHUNK_SIZE * BLOCK_SIZE

//Block stuff
	#define BLOCK_SIZE				1
	
//Vector
	extern guVector UP_VECTOR;
	extern guVector DOWN_VECTOR;
	
#endif

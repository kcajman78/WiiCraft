// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#ifndef _CHUNKHANDLER_HPP_
#define _CHUNKHANDLER_HPP_

#include <stdio.h>
#include <vector>
#include "Math_utils.h"
#include "Chunk.hpp"
#include "Wiicraft.hpp"


class ChunkHandler
{
public:
//Constructor
	ChunkHandler(Vertex32 *pos);
//Destructor
	~ChunkHandler();
//Methods
	Chunk *getChunkP(int x, int y, int z) {return chunkList[getWorldIndex(x,y,z)];}
	Block *getBlockAtPosition(int x, int y, int z);
	bool chunkInBounds(Chunk *chunkPointer);
	void clearChunkList();
	void updateChunks();
	void generateNeighbours();
	void draw();
	void setChunkToUpdate(Chunk *chunkPointer) {if(chunkPointer != NULL) chunkPointer->needsUpdate = true;}
	
//Variables
	Vertex32 *position;
	std::vector<Chunk *> chunkList;
};

#endif

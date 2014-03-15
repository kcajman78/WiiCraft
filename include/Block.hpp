// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

#include <gccore.h>
#include <Math_utils.h>
#include <BoundingBox.hpp>
#include <Wiicraft.hpp>
#include <Chunk.hpp>
//#include "map.h"

class Chunk;

class Block
{
public:
//Constructor
	Block(Chunk *chunkP, int pos_x, int pos_y, int pos_z, int ID2);
//Destructor
	~Block();
//Methods

//Variables
//private:
	Chunk *chunkPointer;
	uint8_t ID;
	bool transparent;
	Block & operator=(const Block &rhs);
};



#endif

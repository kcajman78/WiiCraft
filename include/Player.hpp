// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include "utils.h"
#include "Math_utils.h"
#include "Chunk.hpp"
#include "ChunkHandler.hpp"
#include "BoundingBox.hpp"
#include "Camera.hpp"

enum
{
	ON_AIR = 0,
	ON_GROUND = 1
};

class Player
{
public:
//Constructor
	Player(MtxP view, float init_x, float init_y, float init_z);
	Player(float init_x, float init_y, float init_z);
//Destructor
	~Player();
	
	
//Methods
	//View Matrix
		void updateViewMatrix(){camera->updateViewMatrix();}
	//Move and translate
		void moveVelocity(float acceleration, guVector direction, float time);
		void move(float distance, guVector direction);
		void movePosition(float distance, guVector direction, float time);
		void translate(float x, float y, float z);
	//Update
		void update();
	//Set to old position
		void setToOldPosition();
	//Camera

	
	
//Variables
	guVector position, oldPosition, cameraPosition;
	guVector velocity;
	int chunk_x, chunk_y, chunk_z;
	int block_x, block_y, block_z;
	float pitch, yaw;
	uint8_t status;
	Camera *camera;
	float eyeHeight;
	BoundingBox *boundingBox;
	bool canFly;
};




#endif

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#include "Player.hpp"


//Constructor
	Player::Player(MtxP view, float init_x, float init_y, float init_z)
	{	
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		velocity.z = 0.0f;
		
		eyeHeight = 1.75;
		boundingBox = new BoundingBox(0, 0, 0, 0, eyeHeight, 0.0f);
		
		camera = new Camera(view, &cameraPosition, &pitch, &yaw);
		cameraPosition.x = position.x = oldPosition.x = init_x;
		cameraPosition.y = position.y = oldPosition.y = init_y;
		cameraPosition.z = position.z = oldPosition.z = init_z;
		
		cameraPosition.y += eyeHeight;
		
		yaw = 0.0f;
		pitch = 0.0f;
		status = ON_AIR;
	}
	
	Player::Player(float init_x, float init_y, float init_z)
	{
		position.x = init_x;
		position.y = init_y;
		position.z = init_z;
		yaw = 0.0f;
		pitch = 0.0f;
		status = ON_AIR;
	}	
//Destructor
	Player::~Player()
	{
		delete camera;
		delete boundingBox;
	}
	
//Methods	
	//Move and translate
	
		void Player::move(float distance, guVector direction)
		{
			position.x += (direction.x * distance);
			position.y += (direction.y * distance);
			position.z += (direction.z * distance);
		}
			
		void Player::movePosition(float distance, guVector direction, float time)
		{
			position.x += (direction.x * distance) * time;
			position.y += (direction.y * distance) * time;
			position.z += (direction.z * distance) * time;
		}
		
		void Player::moveVelocity(float acceleration, guVector direction, float time)
		{
			velocity.x += (direction.x * acceleration) * time;
			velocity.y += (direction.y * acceleration) * time;
			velocity.z += (direction.z * acceleration) * time;
		}
		
		void Player::translate(float x, float y, float z)
		{
			position.x = x;
			position.y = y;
			position.z = z;
		}	
		
	//Update
		void Player::update()
		{
			//Old position
				oldPosition.x = position.x;
				oldPosition.y = position.y;
				oldPosition.z = position.z;
			//Velocity
				position.x += velocity.x;
				position.y += velocity.y;
				position.z += velocity.z;
			//Camera
				cameraPosition.x = position.x;
				cameraPosition.y = position.y + eyeHeight;
				cameraPosition.z = position.z;
				
				if(yaw > PI_2) yaw -= PI_2;
				if(yaw < -PI_2) yaw += PI_2;
				if(pitch > HALF_PI) pitch = HALF_PI;
				if(pitch < -HALF_PI) pitch = -HALF_PI;
			//World limits
				if(position.x > WORLD_TOTAL_SIZE) position.x = WORLD_TOTAL_SIZE - 0.0001;
				if(position.y > WORLD_TOTAL_SIZE) position.y = WORLD_TOTAL_SIZE - 0.0001;
				if(position.z > WORLD_TOTAL_SIZE) position.z = WORLD_TOTAL_SIZE - 0.0001;

				if(position.x < 0) position.x = 0.0001;
				if(position.y < 0) position.y = 0.0001;
				if(position.z < 0) position.z = 0.0001;
			//Bounding box
				boundingBox->box.x = position.x;
				boundingBox->box.y = position.y;
				boundingBox->box.z = position.z;
			//Chunk and block
				chunk_x = floor(position.x / CHUNK_TOTAL_SIZE);
				chunk_y = floor(position.y / CHUNK_TOTAL_SIZE);
				chunk_z = floor(position.z / CHUNK_TOTAL_SIZE);
				block_x = floor((position.x - (chunk_x * CHUNK_TOTAL_SIZE)) / BLOCK_SIZE);
				block_y = floor((position.y - (chunk_y * CHUNK_TOTAL_SIZE)) / BLOCK_SIZE);
				block_z = floor((position.z - (chunk_z * CHUNK_TOTAL_SIZE)) / BLOCK_SIZE);		
		}
		
	//Set to old the position
		void Player::setToOldPosition()
		{
			position.x = oldPosition.x;
			position.y = oldPosition.y;
			position.z = oldPosition.z;			
		}		


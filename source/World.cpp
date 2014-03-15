// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#include "World.hpp"


//Constructor
	World::World()
	{
		worldPosition.x = 0; worldPosition.y = 0; worldPosition.z = 0;
	//ChunkHandler
		chunkHandler = new ChunkHandler(&worldPosition);
	//Player
		player = new Player((MtxP)cameraView, WORLD_TOTAL_SIZE/2.0, WORLD_TOTAL_SIZE/2.0f + 6.0f, WORLD_TOTAL_SIZE/2.0);
	}
	
//Destructor
	World::~World()
	{
		delete chunkHandler;
		delete player;
	}

//Methods
	
	void World::updateControls()
	{
		WPAD_ScanPads();
		WPAD_Probe(0, &wiimoteExpansion);	
		wiimoteData = WPAD_Data(0);
		nunchukJoystick = &wiimoteData->exp.nunchuk.js;
	}
	
	void World::movePlayer()
	{
		if(wiimoteExpansion == WPAD_EXP_NUNCHUK)
		{
			if(wiimoteData->btns_h & WPAD_NUNCHUK_BUTTON_Z)
			{
				if(player->status == ON_GROUND)
				{
					player->status = ON_AIR;
					player->moveVelocity(250.0f, UP_VECTOR, 0.0004f);
				}
			}
			if(nunchukJoystick->mag >= 0.2f)
			{
				float n_angle = DegToRad(NunchukAngle(nunchukJoystick->ang));
				player->move( cos(n_angle)*nunchukJoystick->mag / 7.5f, player->camera->getRightVector());
				player->move(-sin(n_angle)*nunchukJoystick->mag / 7.5f, player->camera->getForwardVector());	
			}
		}
		
		if(wiimoteData->btns_h & WPAD_BUTTON_UP)
			player->pitch += 0.02f;
		if(wiimoteData->btns_h & WPAD_BUTTON_DOWN)
			player->pitch -= 0.02f;

		if(wiimoteData->btns_h & WPAD_BUTTON_RIGHT)
			player->yaw -= 0.02f;
		if(wiimoteData->btns_h & WPAD_BUTTON_LEFT)
			player->yaw += 0.02f;		
	}


	Block *World::getBlockUnderPlayer(Vertex32 *block_pos)
	{
		return chunkHandler->getChunkP(player->chunk_x, player->chunk_y, player->chunk_z)->
							getBlockP(player->block_x, player->block_y, player->block_z);
	}
	
	void World::getBlockBoundingBox(int chunk_x, int chunk_y, int chunk_z, int block_x, int block_y, int block_z, BoundingBox *bBox)
	{
		if(bBox != NULL)
		{
			bBox->box.x = chunk_x * CHUNK_TOTAL_SIZE + block_x * BLOCK_SIZE;
			bBox->box.y = chunk_y * CHUNK_TOTAL_SIZE + block_y * BLOCK_SIZE;
			bBox->box.z = chunk_z * CHUNK_TOTAL_SIZE + block_z * BLOCK_SIZE;
			bBox->box.w = BLOCK_SIZE;
			bBox->box.h = BLOCK_SIZE;
			bBox->box.d = BLOCK_SIZE;
		}
	}

	void World::updatePlayerPhysics()
	{
		//Move player
			movePlayer();
		//Update player
			player->update();		

		if(player->status == ON_AIR)
		{
			//Gravity
				player->moveVelocity(worldGravity, DOWN_VECTOR, 0.00035f);
			
			Block *bp = getBlockUnderPlayer(NULL);
			
			if(bp != NULL)
			{
				if(not (bp->transparent))
				{
					player->status = ON_GROUND;
					player->velocity.y = 0.0f;	
				}	
			}
		}
		if(player->status == ON_GROUND)
		{
			Block *bp = getBlockUnderPlayer(NULL);
			if(bp != NULL)
			{
				if(not bp->chunkPointer->isSolid(bp))
				{
					player->status = ON_AIR;
				}
			}
			
		}
		
	}

	void World::update()
	{
		//Update controls
			updateControls();
		//Update chunks
			chunkHandler->updateChunks();
		//Update player
			updatePlayerPhysics();
		//Update view matrix
			player->camera->updateViewMatrix();
	}

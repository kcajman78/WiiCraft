// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#include "Chunk.hpp"
//#include "SingletonMap.h" DONT WORKS YET! SingletonMap::Instance()->mainMAP.mapArray[z][y][x]
#include "map.h"
//MAP mainMAP;

//Constructor
	Chunk::Chunk(int pos_x, int pos_y, int pos_z, int index_x, int index_y, int index_z, bool transp)
	{
		position.x = pos_x; position.y = pos_y; position.z = pos_z;
		index.x = index_x; index.y = index_y; index.z = index_z;
		initBlocks(transp);
		mesh = new Mesh(GX_QUADS, GX_VTXFMT0);
		needsUpdate = true;
	}


//Destructor
	Chunk::~Chunk()
	{
		deleteBlocks();
		delete mesh;
	}

//Methods
	void Chunk::initBlocks(bool transp)
	{
		
		for(int z = 0;  z < CHUNK_SIZE; z++)
		{
			for(int y = 0;  y < CHUNK_SIZE; y++)
			{
				for(int x = 0;  x < CHUNK_SIZE; x++)
				{
					blockList[z][y][x] = new Block(this,
													position.x + x * BLOCK_SIZE,
													position.y + y * BLOCK_SIZE,
													position.z + z * BLOCK_SIZE,
													'0'//seeGeneratedMapBlock(z, y, x)
												);
					blockList[z][y][x]->transparent = transp;  //<<<<<<<<<<<<<<<<<<<<!!!!!!!!!!!!!!
				}	
			}			
		}
		//blockList[2][2][2]->transparent = true;
	}
	
	void Chunk::deleteBlocks()
	{
		for(int z = 0;  z < CHUNK_SIZE; z++)
		{
			for(int y = 0;  y < CHUNK_SIZE; y++)
			{
				for(int x = 0;  x < CHUNK_SIZE; x++)
				{
					delete blockList[z][y][x];		
				}		
			}	
		}
	}
	
	bool Chunk::isSolid(Block *bp)
	{
		if(bp == NULL) return false;
		if(bp->transparent || bp->ID == 0) //ID 0 = AIR
		{
			return false;		
		}
		return true;
	}
		
	bool Chunk::isTransparent(Block *bp)
	{
		if(bp == NULL) return false;
		if(bp->transparent || bp->ID == 0) //ID 0 = AIR
		{
			return true;		
		}
		return false;
	}
	
	void Chunk::generateMesh()
	{
		//Clear current mesh data
			mesh->clearMeshData();
		Block *bp;
		bool addLeft, addRight, addUp, addDown, addFront, addBack;
		for(int z = 0;  z < CHUNK_SIZE; z++)
		{
			for(int y = 0;  y < CHUNK_SIZE; y++)
			{		
				for(int x = 0;  x < CHUNK_SIZE; x++)
				{
					bp = blockList[z][y][x];
					if(bp->transparent) continue;
					
					//Check Left
						if(x == 0)
						{
							if(leftNeighbour != NULL)
								addLeft = leftNeighbour->isTransparent((CHUNK_SIZE-1), y, z);
							else
								addLeft = false;
						}
						else
						{
							addLeft = isTransparent(x - 1, y, z);
						}
						
					//Check Right
						if(x == (CHUNK_SIZE-1))
						{
							if(rightNeighbour != NULL)
								addRight = rightNeighbour->isTransparent(0, y, z);
							else
								addRight = false;
						}
						else
						{
							addRight = isTransparent(x + 1, y, z);
						}

					//Check Down
						if(y == 0)
						{
							if(downNeighbour != NULL)
								addDown = downNeighbour->isTransparent(x, (CHUNK_SIZE-1), z);
							else
								addDown = false;
						}
						else
						{
							addDown = isTransparent(x, y - 1, z);
						}
						
					//Check Up
						if(y == (CHUNK_SIZE-1))
						{
							if(upNeighbour != NULL)
								addUp = upNeighbour->isTransparent(x, 0, z);
							else
								addUp = false;
						}
						else
						{
							addUp = isTransparent(x, y + 1, z);
						}
						
					//Check Back
						if(z == 0)
						{
							if(backNeighbour != NULL)
								addBack = backNeighbour->isTransparent(x, y, (CHUNK_SIZE-1));
							else
								addBack = false;								
						}
						else
						{
							addBack = isTransparent(x, y, z - 1);
						}
						
					//Check Front
						if(z == (CHUNK_SIZE-1))
						{
							if(frontNeighbour != NULL)
								addFront = frontNeighbour->isTransparent(x, y, 0);
							else
								addFront = false;
						}
						else
						{
							addFront = isTransparent(x, y, z + 1);
						}
				//Add to the mesh
					int block_x = position.x + x * BLOCK_SIZE;
					int block_y = position.y + y * BLOCK_SIZE;
					int block_z = position.z + z * BLOCK_SIZE;
					
					//Left
						if(addLeft)
						{
							mesh->addData(block_x, block_y, block_z, 1.0f, 1.0f);
							mesh->addData(block_x, block_y, block_z + BLOCK_SIZE, 0.0f, 1.0f);
							mesh->addData(block_x, block_y + BLOCK_SIZE, block_z + BLOCK_SIZE, 0.0f, 0.0f);
							mesh->addData(block_x, block_y + BLOCK_SIZE, block_z, 1.0f, 0.0f);
						}
					//Right
						if(addRight)
						{
							mesh->addData(block_x + BLOCK_SIZE, block_y, block_z, 1.0f, 1.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y, block_z + BLOCK_SIZE, 0.0f, 1.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y + BLOCK_SIZE, block_z + BLOCK_SIZE, 0.0f, 0.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y + BLOCK_SIZE, block_z, 1.0f, 0.0f);	
						}
					
					//UP
						if(addUp)
						{
							mesh->addData(block_x, block_y + BLOCK_SIZE, block_z, 0.0f, 0.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y + BLOCK_SIZE, block_z, 1.0f, 0.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y + BLOCK_SIZE, block_z + BLOCK_SIZE, 1.0f, 1.0f);
							mesh->addData(block_x, block_y + BLOCK_SIZE, block_z + BLOCK_SIZE, 0.0f, 1.0f);	
						}
					//Down	
						if(addDown)
						{
							mesh->addData(block_x, block_y, block_z, 0.0f, 0.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y, block_z, 0.0f, 1.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y, block_z + BLOCK_SIZE, 1.0f, 1.0f);
							mesh->addData(block_x, block_y, block_z + BLOCK_SIZE, 1.0f, 0.0f);	
						}
					//Front
						if(addFront)
						{
							mesh->addData(block_x, block_y, block_z + BLOCK_SIZE, 0.0f, 1.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y, block_z + BLOCK_SIZE, 1.0f, 1.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y + BLOCK_SIZE, block_z + BLOCK_SIZE, 1.0f, 0.0f);
							mesh->addData(block_x, block_y + BLOCK_SIZE, block_z + BLOCK_SIZE, 0.0f, 0.0f);
						}
					//Back
						if(addBack)
						{
							mesh->addData(block_x, block_y, block_z, 0.0f, 1.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y, block_z, 1.0f, 1.0f);
							mesh->addData(block_x + BLOCK_SIZE, block_y + BLOCK_SIZE, block_z, 1.0f, 0.0f);
							mesh->addData(block_x, block_y + BLOCK_SIZE, block_z, 0.0f, 0.0f);
						}	
				}
			}
		}
		
		needsUpdate = false;
	}
	
	void Chunk::draw()
	{
		mesh->draw();
	}
	
	


// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#ifndef _BOUNDINGBOX_HPP_
#define _BOUNDINGBOX_HPP_

#include "Math_utils.h"

typedef struct
{
	float x, y, z;
	float w, h, d;
}Box;


class BoundingBox
{
public:

//Constructor
	BoundingBox(){}
	BoundingBox(float x, float y, float z, float w, float h, float d)	{box = (Box){x,y,z,w,h,d};}
	BoundingBox(guVector pos, float w, float h, float d)				{box = (Box){pos.x,pos.y,pos.z,w,h,d};}
	BoundingBox(guVector *pos, float w, float h, float d)				{box = (Box){pos->x,pos->y,pos->z,w,h,d};}
	BoundingBox(Vertex32 pos, float w, float h, float d)				{box = (Box){pos.x,pos.y,pos.z,w,h,d};}
	BoundingBox(Vertex32 *pos, float w, float h, float d)				{box = (Box){pos->x,pos->y,pos->z,w,h,d};}
	BoundingBox(guVector pos, guVector size)							{box = (Box){pos.x,pos.y,pos.z,size.x,size.y,size.z};}
	BoundingBox(guVector *pos, guVector *size)							{box = (Box){pos->x,pos->y,pos->z,size->x,size->y,size->z};}
	
//Inline methods
	bool dotCollision(guVector dot)
	{
		if( (dot.x >= box.x) && (dot.x <= (box.x + box.w)) && 
			(dot.y >= box.y) && (dot.y <= (box.y + box.h)) && 
			(dot.z >= box.z) && (dot.z <= (box.z + box.d)) )
			return true;
			
		return false;	
	}
	
	bool dotCollision(guVector *dot)
	{
		if( (dot->x >= box.x) && (dot->x <= (box.x + box.w)) && 
			(dot->y >= box.y) && (dot->y <= (box.y + box.h)) && 
			(dot->z >= box.z) && (dot->z <= (box.z + box.d)) )
			return true;
			
		return false;	
	}
	
	bool dotCollision(Vertex32 dot)
	{
		if( (dot.x >= box.x) && (dot.x <= (box.x + box.w)) && 
			(dot.y >= box.y) && (dot.y <= (box.y + box.h)) && 
			(dot.z >= box.z) && (dot.z <= (box.z + box.d)) )
			return true;
			
		return false;	
	}	
	
	bool dotCollision(Vertex32 *dot)
	{
		if( (dot->x >= box.x) && (dot->x <= (box.x + box.w)) && 
			(dot->y >= box.y) && (dot->y <= (box.y + box.h)) && 
			(dot->z >= box.z) && (dot->z <= (box.z + box.d)) )
			return true;
			
		return false;	
	}	
	
	bool dotCollision(float x, float y, float z)
	{
		if( (x >= box.x) && (x <= (box.x + box.w)) && 
			(y >= box.y) && (y <= (box.y + box.h)) && 
			(z >= box.z) && (z <= (box.z + box.d)) )
			return true;
			
		return false;	
	}
	
	bool boxCollision(BoundingBox bbox)
	{
		if( ((bbox.box.x + bbox.box.w) >= box.x) && (bbox.box.x <= (box.x + box.w)) &&
			((bbox.box.y + bbox.box.h) >= box.y) && (bbox.box.y <= (box.y + box.h)) &&
			((bbox.box.z + bbox.box.d) >= box.z) && (bbox.box.z <= (box.z + box.d)) )
			return true;
	
		return false;
	}
	
	bool boxCollision(BoundingBox *bbox)
	{
		if( ((bbox->box.x + bbox->box.w) >= box.x) && (bbox->box.x <= (box.x + box.w)) &&
			((bbox->box.y + bbox->box.h) >= box.y) && (bbox->box.y <= (box.y + box.h)) &&
			((bbox->box.z + bbox->box.d) >= box.z) && (bbox->box.z <= (box.z + box.d)) )
			return true;
	
		return false;
	}
	
	bool boxCollision(Box _box)
	{
		if( ((_box.x + _box.w) >= box.x) && (_box.x <= (box.x + box.w)) &&
			((_box.y + _box.h) >= box.y) && (_box.y <= (box.y + box.h)) &&
			((_box.z + _box.d) >= box.z) && (_box.z <= (box.z + box.d)) )
			return true;
	
		return false;
	}
	
	bool boxCollision(Box *_box)
	{
		if( ((_box->x + _box->w) >= box.x) && (_box->x <= (box.x + box.w)) &&
			((_box->y + _box->h) >= box.y) && (_box->y <= (box.y + box.h)) &&
			((_box->z + _box->d) >= box.z) && (_box->z <= (box.z + box.d)) )
			return true;
	
		return false;
	}
	
	bool boxCollision(int x, int y, int z, int w, int h, int d)
	{
		if( ((x + w) >= box.x) && (x <= (box.x + box.w)) &&
			((y + h) >= box.y) && (y <= (box.y + box.h)) &&
			((z + d) >= box.z) && (z <= (box.z + box.d)) )
			return true;
	
		return false;
	}
	
	bool boxCollision(Vertex32 *pos, int w, int h, int d)
	{
		if( ((pos->x + w) >= box.x) && (pos->x <= (box.x + box.w)) &&
			((pos->y + h) >= box.y) && (pos->y <= (box.y + box.h)) &&
			((pos->z + d) >= box.z) && (pos->z <= (box.z + box.d)) )
			return true;
	
		return false;
	}

//Methods
//Variables
	Box box;
	
};







#endif

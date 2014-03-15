// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#include "DisplayList.h"


//Constructor
DisplayList::DisplayList()
{	
	cleanColorList();
	cleanPositionList();
}


//Methods
int DisplayList::addColor(uint8_t *colP)
{
	if((col_index + 3) < COL_LIST_SIZE)
	{
		/*col_list[col_index++] = colP[0]; //R
		col_list[col_index++] = colP[1]; //G
		col_list[col_index++] = colP[2]; //B*/
		return 1;
	}
	return 0;
}

int DisplayList::addColor(float r, float g, float b, float a)
{
	if((col_index + 4) < COL_LIST_SIZE)
	{
		col_list[col_index++] = (uint8_t)255*r; //R
		col_list[col_index++] = (uint8_t)255*g; //G
		col_list[col_index++] = (uint8_t)255*b; //B
		col_list[col_index++] = (uint8_t)255*a; //A
		

		return 1;
	}
	return 0;		
}

int DisplayList::addColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	if((col_index + 4) < COL_LIST_SIZE)
	{
		col_list[col_index++] = r; //R
		col_list[col_index++] = g; //G
		col_list[col_index++] = b; //B
		col_list[col_index++] = a; //A
		return 1;
	}
	return 0;			
}

int DisplayList::addPosition(float x, float y, float z)
{
	if((pos_index + 3) < POS_LIST_SIZE)
	{
		pos_list[pos_index++] = x;
		pos_list[pos_index++] = y;
		pos_list[pos_index++] = z;
		
		return 1;
	}
	return 0;		
}


int DisplayList::addPosition(float *posP)
{
	if((pos_index+3) < POS_LIST_SIZE)
	{
		pos_list[pos_index++] = posP[0];
		pos_list[pos_index++] = posP[1];
		pos_list[pos_index++] = posP[2];
		return 1;
	}
	return 0;
}

void DisplayList::renderList()
{	
			
	GX_SetArray (GX_VA_POS,  pos_list, sizeof(float) * 3);
	GX_SetArray (GX_VA_CLR0, col_list, sizeof(uint8_t) * 4);


	GX_Begin(GX_QUADS, GX_VTXFMT0, pos_index);
		for(uint16_t i = 0; i < pos_index ; i++)
		{
			GX_Color1x16(i);
			GX_Position1x16(i);			

		}	
	GX_End ();	
	
	//DCFlushRange(col_list, COL_LIST_SIZE);
	//DCFlushRange(pos_list, POS_LIST_SIZE);		
	
}

void DisplayList::cleanColorList()
{
	col_index = 0;
	memset(col_list, 0, COL_LIST_SIZE);			
}

void DisplayList::cleanPositionList()
{
	pos_index = 0;
	memset(pos_list, 0, POS_LIST_SIZE);	
}

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <vector>
#include <stdio.h>
#include "Math_utils.h"


typedef struct
{
	int x, y, z;
	float u, v;
}TexVertex;


class Mesh
{
public:
//Constructor
	Mesh(uint8_t prm, uint8_t vtxFmt);
//Destructor
	~Mesh();
//Methods
	void clearMeshData() {meshData.clear();}
	void addData(int x, int y, int z, float u , float v) {meshData.push_back((TexVertex){x, y, z, u, v});}
	void addData(TexVertex texVtx) {meshData.push_back(texVtx);}
	void setVertexFormat(uint8_t vtxFmt)  {vertexFormat = vtxFmt;}
	void setPrimitive(uint8_t  prm) {vertexFormat = prm;}
	uint32_t size() {return meshData.size();}
	void draw();
	
	
	std::vector<TexVertex> meshData;
	uint8_t vertexFormat;
	uint8_t primitive;
};

#endif

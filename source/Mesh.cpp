// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#include "Mesh.hpp"

//Constructor
	Mesh::Mesh(uint8_t prm, uint8_t vtxFmt)
	{
		setPrimitive(prm);
		setVertexFormat(vtxFmt);
	}
	
//Destructor
	Mesh::~Mesh()
	{
		clearMeshData();
	}
//Methods
	void Mesh::draw()
	{
		std::vector<TexVertex>::iterator it;		
		GX_Begin(GX_QUADS, GX_VTXFMT0,  meshData.size());
		for(it = meshData.begin(); it != meshData.end(); it++)
		{
			GX_Position3f32(it->x, it->y, it->z);
			GX_TexCoord2f32(it->u, it->v);		
		}
		GX_End();
	}

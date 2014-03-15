// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#include "Math_utils.h"


//Converts spherical(phi, theta, rho) coordinates to cartesian coordinates (x,y,z)
	guVector spherical_to_cartesian(float phi, float theta, float rho)
	{
		guVector v;
		
		v.x = cosf(phi) * sinf(theta) * rho;
		v.y = sinf(theta) * rho;
		v.z = sinf(phi) * sinf(theta) * rho;
		
		return v;
	}
	

////Converts spherical(phi, theta, rho) coordinates to cartesian coordinates (x,y,z) normalized
	guVector spherical_to_cartesian_norm(float phi, float theta)
	{
		guVector v;
		
		v.x = cosf(phi) * cosf(theta);
		v.y = sinf(theta);
		v.z = sinf(phi) * sinf(theta);
		
		return v;	
	}

//Cross product between a and b
	guVector cross_product(guVector a, guVector b)
	{
		guVector c;
		
		c.x = a.y * b.z - a.z * b.y;
		c.y = a.z * b.x - a.x * b.z;
		c.z = a.x * b.y - a.y * b.x;			
		
		return c;
	}

//Dot product between a and b
	float dot_product(guVector a, guVector b)
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;				
	}

//Vector length/magnitude
	float vector_length(guVector v)
	{
		return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
	}

//Normalize vector
	guVector vector_normalize(guVector v)
	{
		float length = vector_length(v);
		
		return (guVector){v.x/length, v.y/length, v.z/length};
	}
//Get angle (theta) between a and b
	float vector_theta(guVector a, guVector b)
	{
		float theta = acosf(dot_product(vector_normalize(a), vector_normalize(b)));
		return theta;
	}

//Zeroes a vector
	void vector_zero(guVector *v)
	{
		v->x = 0.0f;
		v->y = 0.0f;
		v->z = 0.0f;
	}	
	
	
	
	
/****************************  MATRIX **************************/

//Set matrix rotation X
	void matrix_set_rotation_x(MtxP m, float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);
		
		m[1][1] = c;
		m[1][2] = s;
		
		m[2][1] = -s;
		m[2][2] = c;
	}
	
//Set matrix rotation Y
	void matrix_set_rotation_y(MtxP m, float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);
		
		m[0][0] = c;
		m[0][2] = -s;
		
		m[2][0] = s;
		m[2][2] = c;		
	}
	
//Set matrix rotation Z
	void matrix_set_rotation_z(MtxP m, float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);
		
		m[0][0] = c;
		m[0][1] = -s;
		
		m[1][0] = s;
		m[1][1] = c;		
	}
	
	
//Translate matrix (x,y,z)
	void matrix_translate(MtxP m, float x, float y, float z)
	{	
		m[0][3] = m[0][0]*x + m[0][1]*y + m[0][2]*z;
		m[1][3] = m[1][0]*x + m[1][1]*y + m[1][2]*z;
		m[2][3] = m[2][0]*x + m[2][1]*y + m[2][2]*z;
	}
	

//Matrix 3x3 identity
	void matrix_3x3_identity(MtxP m)
	{
		float *p = (float *)m;
		
		p[0] = p[4] = p[8] = 1.0f;
		p[1] = p[2] = p[3] = 
		p[5] = p[6] = p[7] = 0.0f;
	}
	
//Matrix 4x4 identity
	void matrix_4x4_identity(Mtx44 m)
	{
		float *p = (float *)m;	
		p[0] =  p[5] =  p[10] = p[15] = 1.0;
		p[1] =  p[2] =  p[3] =  p[4] = 0.0;
		p[6] =  p[7] =  p[8] =  p[9] = 0.0;
		p[11] = p[12] = p[13] = p[14] = 0.0;
	}
	
//Rotate matrix around X axis
	void matrix_rotate_x(MtxP m, float angle)
	{
		Mtx r;
		guMtxIdentity(r);
		matrix_set_rotation_x(r, angle);
		
		guMtxConcat(m, r, m);	
	}
	
//Rotate matrix around Y axis
	void matrix_rotate_y(MtxP m, float angle)
	{
		Mtx r;
		guMtxIdentity(r);
		matrix_set_rotation_y(r, angle);
		
		guMtxConcat(m, r, m);		
	}
	
//Rotate matrix around Z axis
	void matrix_rotate_z(MtxP m, float angle)
	{
		Mtx r;
		guMtxIdentity(r);
		matrix_set_rotation_z(r, angle);
		
		guMtxConcat(m, r, m);		
	}
	
//Multply matrix (if m1 and dest should be different!!)
	void matrix_mult(MtxP m1, MtxP m2, MtxP dest)
	{
		dest[0][0] = m1[0][0]*m2[0][0] + m1[0][1]*m2[1][0] + m1[0][2]*m2[2][0];
		dest[0][1] = m1[0][0]*m2[0][1] + m1[0][1]*m2[1][1] + m1[0][2]*m2[2][1];
		dest[0][2] = m1[0][0]*m2[0][2] + m1[0][1]*m2[1][2] + m1[0][2]*m2[2][2];
		dest[0][3] = m1[0][0]*m2[0][3] + m1[0][1]*m2[1][3] + m1[0][2]*m2[2][3] + m1[0][3];

		dest[1][0] = m1[1][0]*m2[0][0] + m1[1][1]*m2[1][0] + m1[1][2]*m2[2][0];
		dest[1][1] = m1[1][0]*m2[0][1] + m1[1][1]*m2[1][1] + m1[1][2]*m2[2][1];
		dest[1][2] = m1[1][0]*m2[0][2] + m1[1][1]*m2[1][2] + m1[1][2]*m2[2][2];
		dest[1][3] = m1[1][0]*m2[0][3] + m1[1][1]*m2[1][3] + m1[1][2]*m2[2][3] + m1[1][3];

		dest[2][0] = m1[2][0]*m2[0][0] + m1[2][1]*m2[1][0] + m1[2][2]*m2[2][0];
		dest[2][1] = m1[2][0]*m2[0][1] + m1[2][1]*m2[1][1] + m1[2][2]*m2[2][1];
		dest[2][2] = m1[2][0]*m2[0][2] + m1[2][1]*m2[1][2] + m1[2][2]*m2[2][2];
		dest[2][3] = m1[2][0]*m2[0][3] + m1[2][1]*m2[1][3] + m1[2][2]*m2[2][3] + m1[2][3];	
	}
	
//Multply 3x3 matrix
	void matrix_3x3_mult(MtxP m1, MtxP m2, MtxP dest)
	{
		dest[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0];
		dest[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1];
		dest[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2];
		 
		dest[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0];
		dest[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1]; 
		dest[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2];
		 
		dest[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0];
		dest[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1];
		dest[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2];
	}
	
//Multply 4x4 matrix
	void matrix_4x4_mult(Mtx44 m1, Mtx44 m2, Mtx44 dest)
	{
		dest[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0] + m1[0][3] * m2[3][0]; 
		dest[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1] + m1[0][3] * m2[3][1]; 
		dest[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2] + m1[0][3] * m2[3][2]; 
		dest[0][3] = m1[0][0] * m2[0][3] + m1[0][1] * m2[1][3] + m1[0][2] * m2[2][3] + m1[0][3] * m2[3][3];
		 
		dest[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0] + m1[1][3] * m2[3][0]; 
		dest[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1] + m1[1][3] * m2[3][1]; 
		dest[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2] + m1[1][3] * m2[3][2]; 
		dest[1][3] = m1[1][0] * m2[0][3] + m1[1][1] * m2[1][3] + m1[1][2] * m2[2][3] + m1[1][3] * m2[3][3];
		 
		dest[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0] + m1[2][3] * m2[3][0]; 
		dest[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1] + m1[2][3] * m2[3][1]; 
		dest[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2] + m1[2][3] * m2[3][2]; 
		dest[2][3] = m1[2][0] * m2[0][3] + m1[2][1] * m2[1][3] + m1[2][2] * m2[2][3] + m1[2][3] * m2[3][3]; 

		dest[3][0] = m1[3][0] * m2[0][0] + m1[3][1] * m2[1][0] + m1[3][2] * m2[2][0] + m1[3][3] * m2[3][0]; 
		dest[3][1] = m1[3][0] * m2[0][1] + m1[3][1] * m2[1][1] + m1[3][2] * m2[2][1] + m1[3][3] * m2[3][1]; 
		dest[3][2] = m1[3][0] * m2[0][2] + m1[3][1] * m2[1][2] + m1[3][2] * m2[2][2] + m1[3][3] * m2[3][2]; 
		dest[3][3] = m1[3][0] * m2[0][3] + m1[3][1] * m2[1][3] + m1[3][2] * m2[2][3] + m1[3][3] * m2[3][3]; 
	}

	bool box_collision(float x1, float y1, float z1, float box_size, float x2, float y2, float z2)
	{
		if( (x2 >= x1) && (x2 <= (x1+box_size)) && (y2 >= y1) && (y2 <= (y1+box_size)) && (z2 >= z1) && (z2 <= (z1+box_size)) )
		{
			return true;	
		}
		return false;
	}


	bool block_collision(int chunk_x, int chunk_y, int chunk_z, int block_x, int block_y, int block_z, float pos_x, float pos_y, float pos_z)
	{
		/*float block_pos_x = chunk_x * CHUNK_TOTAL_SIZE + block_x * BLOCK_SIZE;
		float block_pos_y = chunk_y * CHUNK_TOTAL_SIZE + block_y * BLOCK_SIZE; 
		float block_pos_z = chunk_z * CHUNK_TOTAL_SIZE + block_z * BLOCK_SIZE; 
		return box_collision(block_pos_x, block_pos_y, block_pos_z, BLOCK_SIZE, pos_x, pos_y, pos_z);*/
		return true;
	}
	
	
	
	
	


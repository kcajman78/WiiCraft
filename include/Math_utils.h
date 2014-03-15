// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013      filfat, xerpi, JoostinOnline

#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_


#include <gccore.h>
#include <math.h>
#include <string.h>

#define PI                      3.14159265
#define PI_2            6.28318531
#define HALF_PI         1.57079633

//#define RadtoDeg(x) (x * 57.2957795)
#define cosDEG(x) (cos(DegToRad(x)))
#define sinDEG(x) (sin(DegToRad(x)))
#define vectMAG(x,y,z) (sqrt(x*x + y*y + z*z))

#define NunchukAngle(x) (-x+90)

typedef struct
{
        int16_t x, y, z;
}Vertex16;

typedef struct
{
        int32_t x, y, z;
}Vertex32;

typedef struct
{
        uint8_t r,g,b,a;
}Color4u8;

//Converts spherical(phi, theta, rho) coordinates to cartesian coordinates (x,y,z)
        guVector spherical_to_cartesian(float phi, float theta, float rho);
////Converts spherical(phi, theta, rho) coordinates to cartesian coordinates (x,y,z) normalized
        guVector spherical_to_cartesian_norm(float phi, float theta);
//Cross product between a and b
        guVector cross_product(guVector a, guVector b);
//Dot product between a and b
        float dot_product(guVector a, guVector b);
//Vector length/magnitude
        float vector_length(guVector v);
//Normalize vector
        guVector vector_normalize(guVector v);
//Get angle (theta) between a and b
        float vector_theta(guVector a, guVector b);
//Zeroes a vector
        void vector_zero(guVector *v);
        
//Set matrix rotation X
        void matrix_set_rotation_x(MtxP m, float angle);
//Set matrix rotation Y
        void matrix_set_rotation_y(MtxP m, float angle);
//Set matrix rotation Z
        void matrix_set_rotation_z(MtxP m, float angle);
        
//Translate matrix (x,y,z)
        void matrix_translate(MtxP m, float x, float y, float z);
        
//Matrix 3x3 identity
        void matrix_3x3_identity(MtxP m);
//Matrix 4x4 identity
        void matrix_4x4_identity(Mtx44 m);
        
//Rotate matrix around X axis
        void matrix_rotate_x(MtxP m, float angle);
//Rotate matrix around Y axis
        void matrix_rotate_y(MtxP m, float angle);
//Rotate matrix around Z axis
        void matrix_rotate_z(MtxP m, float angle);
        
//Multply matrix (if m1 and dest should be different!!)
        void matrix_mult(MtxP m1, MtxP m2, MtxP dest);
//Multply 3x3 matrix (if m1 and dest should be different!!)
        void matrix_3x3_mult(MtxP m1, MtxP m2, MtxP dest);
//Multply 4x4 matrix (if m1 and dest should be different!!)
        void matrix_4x4_mult(Mtx44 m1, Mtx44 m2, Mtx44 dest);   
        
//Collisions
        bool box_collision(float x1, float y1, float z1, float box_size, float x2, float y2, float z2);
        bool block_collision(int chunk_x, int chunk_y, int chunk_z, int block_x, int block_y, int block_z, float pos_x, float pos_y, float pos_z);

#endif
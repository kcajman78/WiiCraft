// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <gccore.h>
#include <math.h>
#include <string.h>
#include "utils.h"
#include "Math_utils.h"

class Camera
{
public:
//Constructor
	Camera(MtxP viewP, guVector *positionP, float *pitchP, float *yawP);

//Methods
	guVector getLookVector();
	guVector getUpVector();
	guVector getForwardVector();
	guVector getRightVector();
	void updateViewMatrix();
	//void move(float distance, guVector direction);
	//void translate(float x, float y, float z);
//private:
	guVector *position;
	float *pitch, *yaw;
	
	MtxP viewMatrix;	
};



#endif

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#include "Camera.hpp"

guVector UP_VECTOR = {0.0f, 1.0f, 0.0f};
guVector DOWN_VECTOR = {0.0f, -1.0f, 0.0f};

//Constructor
	Camera::Camera(MtxP viewP, guVector *positionP, float *pitchP, float *yawP)
	{
		viewMatrix = viewP;
		position = positionP;
		pitch = pitchP;
		yaw = yawP;
	}


//Methods
	void Camera::updateViewMatrix()
	{	
		guMtxIdentity(viewMatrix);
		
		matrix_rotate_x(viewMatrix, *pitch);
		matrix_rotate_y(viewMatrix, *yaw);		
		
		matrix_translate(viewMatrix, -position->x, -position->y, -position->z);
		
	}
	
	guVector Camera::getLookVector()
	{		
		float *p = (float *)viewMatrix[2];
		guVector v = {*(p), *(p+1), *(p+2)};
		return v;
	}

	guVector Camera::getForwardVector()
	{		
		return cross_product(getRightVector(), UP_VECTOR);
	}
	
	guVector Camera::getRightVector()
	{
		float *p = (float *)viewMatrix;
		guVector v = {*(p), *(p+1), *(p+2)};
		return v;
	}
	
	guVector Camera::getUpVector()
	{
		float *p = (float *)viewMatrix[1];
		guVector v = {*(p), *(p+1), *(p+2)};
		return v;
	}

/*	void Camera::move(float distance, guVector direction)
	{
		position->x += direction.x * distance;
		position->y += direction.y * distance;
		position->z += direction.z * distance;
	}
	
	void Camera::translate(float x, float y, float z)
	{
		position->x = x;
		position->y = y;
		position->z = z;
	}

*/

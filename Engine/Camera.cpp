#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	camDist = 1;
	mMove = false;

	camRot = new Vec3(0, 0, NULL);
	camPos = new Vec3(0, 0, 0);
}

Camera::Camera(int dist)
{
	camDist = dist;
}

Camera::~Camera()
{
	delete(camRot); 
	delete(camPos);
}

void Camera::zoomout(Vec3 v)
{
	--camDist;
	v.normalize();
//	*camPos -= v * camDist;
}

void Camera::zoomin(Vec3 v)
{
	++camDist;
	v.normalize();
//	*camPos -= v * camDist;
}

void Camera::mouse(const float& rotx, const float& roty,const Vec3* pos)
{
	//look around
	if (!mMove)
	{
	camRot->x += rotx;
	camRot->y += roty;

	if (camRot->x >= 360)
		camRot->x = 0;

	if (camRot->x <0)
		camRot->x = 360;

	if (camRot->y >= 70)
		camRot->y = 70;

	if (camRot->y <-70)
		camRot->y = -70;

	camPos->x = camDist * sin(camRot->y*PI / 180); + pos->x;
	camPos->z = camDist * -cos(camRot->y*PI / 180) + pos->z;

	glutWarpPointer(width / 2, height / 2);
	mMove = true;
	}
	else
		mMove = false;

	
}

void Camera::keyboard(Vec3 & v)
{
}

float Camera::getRot(const char &op)
{
	switch (op)
	{
	case 'X': case 'x':
		return camRot->x;
		break;
	case 'Y': case 'y':
		return camRot->y;
		break;
	}
	return NULL;
}

float Camera::getPos(const char &op)
{
	switch (op)
	{
	case 'X': case 'x':
		return camPos->x;
		break;

	case 'Y': case 'y':
		return camPos->y;

	case 'Z': case 'z':
		return camPos->z;
		break;
	}
	return NULL;
}


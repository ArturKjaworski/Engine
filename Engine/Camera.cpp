#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	camDist = 0;
	mMove = false;

	camRot = Vec3(0,125,0);
	camPos = Vec3();
	if (camDist > 0)
		camType = TPP;
	else
		camType = FPP;
}

Camera::Camera(int dist)
{
	camDist = dist;
	mMove = false;

	camRot = Vec3(0, 125, 0);
	camPos = Vec3();

	if (camDist > 0)
		camType = TPP;
	else
		camType = FPP;
}

Camera::~Camera()
{
}

//on key for now.
void Camera::zoom(Vec3& v, const int& val)
{
	camDist+=val;
	if (camDist <= 0)
	{
		camDist = 0;
		if (camType != FPP)
			camType = FPP;
	}
	else
	{
		if (camType != TPP)
			camType = TPP;

		camPos += v * camDist;
	}
}

void Camera::mouse(const float& rotx, const float& roty,const Vec3& pos)
{
	//look around
	if (!mMove)
	{
	camRot.x += rotx;
	camRot.y += roty;


	if (camRot.y > 170)
		camRot.y = 170;
	if (camRot.y < 0)
		camRot.y = 0;

	if (camDist != 0)
	{
		camPos.x = camDist * sin(camRot.x*PI / 180) + pos.x;
		camPos.z = camDist * -cos(camRot.x*PI / 180) + pos.z;
		camPos.y = camDist * cos(camRot.y*PI / 180) + pos.y;
	}
	else
	{
		camPos.x = 0.001 * sin(camRot.x*PI / 180) + pos.x;
		camPos.z = 0.001 * -cos(camRot.x*PI / 180) + pos.z;
		camPos.y = 0.001 * cos(camRot.y*PI / 180) + pos.y;
	}

		if (camPos.y >= 1)
			camPos.y = 1;

	glutWarpPointer(width / 2, height / 2);
	mMove = true;
	}
	else
		mMove = false;

	
}

float Camera::getRot(const char &op)
{
	switch (op)
	{
	case 'X': case 'x':
		return camRot.x;
		break;
	case 'Y': case 'y':
		return camRot.y;
		break;
	}
	return NULL;
}

float Camera::getPos(const char &op)
{
	switch (op)
	{
	case 'X': case 'x':
		return camPos.x;
		break;

	case 'Y': case 'y':
		return camPos.y;

	case 'Z': case 'z':
		return camPos.z;
		break;
	}
	return NULL;
}


#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	camDist = 2;
	mMove = false;

	camRot = Vec3();
	camPos = Vec3(0,-2,-camDist);
}

Camera::Camera(int dist)
{
	camDist = dist;
}

Camera::~Camera()
{
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

void Camera::mouse(const float& rotx, const float& roty,const Vec3& pos)
{
	//look around
	if (!mMove)
	{
	camRot.x += rotx;
	camRot.y += roty;

	//170 0

	if (camRot.y > 170)
		camRot.y = 170;
	if (camRot.y < 0)
		camRot.y = 0;

		camPos.x = camDist * sin(camRot.x*PI / 180) + pos.x;
		camPos.z = camDist * -cos(camRot.x*PI / 180) + pos.z;

		camPos.y = camDist* cos(camRot.y*PI / 180) + pos.y;
	//camPos.z = camDist * sin(camRot.y*PI / 180); +pos.z;
	//camPos.x = camDist * -cos(camRot.y*PI / 180) + pos.x;
		cout << camRot.y << " "  << endl;
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


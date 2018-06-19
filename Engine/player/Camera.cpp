#include "..\stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	camDist = 0;
	mMove = false;

	camRot = Vec3();
	camPos = Vec3();
	camType = camDist > 0 ? TPP : FPP;
}

Camera::Camera(int dist)
{
	camDist = dist;
	mMove = false;

	camRot = Vec3(0,50, 0);
	camPos = Vec3();
	camType = camDist > 0 ? TPP : FPP;
}

Camera::~Camera()
{
}

//on key for now.  return alpha channel
float Camera::zoom(const int& val)
{
	camDist+=val;
	if (camDist <= 0)
	{
		camDist = 0.1;
		if (camType != FPP)
			camType = FPP;
	}
	else
	{
		if (camType != TPP)
			camType = TPP;
	}
	switch (int(camDist))
	{
	case 1:
	{
		return 0.1;
	}
	case 2:
	{
		return 0.5;
	}
	default:
		return 1;
	}
}

void Camera::look(const float& rotx, const float& roty,const Vec3& pos)
{
	//look around
	if (!mMove)
	{
	camRot.x += rotx;
	camRot.y -= roty;

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

	if (camPos.y <= 0)
	{
		camPos.y = 0;
		//	--camDist;
	}
		

	glutWarpPointer(width / 2, height / 2);
	mMove = true;
	}
	else
		mMove = false;
}

void Camera::look(const Vec3& pos)
{
	if (camDist != 0)
	{
		camPos.x = camDist * sin(camRot.x*PI / 180) + pos.x;
		camPos.z = camDist * -cos(camRot.x*PI / 180) + pos.z;
		camPos.y = camDist * cos(camRot.y*PI / 180) + pos.y;
	}
	else
	{
		camPos.x = 0.1 * sin(camRot.x*PI / 180) + pos.x;
		camPos.z = 0.1 * -cos(camRot.x*PI / 180) + pos.z;
		camPos.y = 0.1 * cos(camRot.y*PI / 180) + pos.y;
	}

	if (camPos.y >= 1)
		camPos.y = 1;

	glutWarpPointer(width / 2, height / 2);
}

void Camera::camMovement(const float& val, const float& spd)
{
//	//camera movement while moving		//right foot first
//	if (val > 0)
//	{
//		if (nStep)
//		{
//			camPos.x += sqrt(1 - val)*0.00001*spd;
//			camPos.z -= sqrt(val)*0.00001*spd;
//		}
//		else
//		{
//			camPos.x -= sqrt(1 - val)*0.00001*spd;
//			camPos.z += sqrt(val)*0.00001*spd;
//		}
//	}else
//		if (nStep)
//		{
//			camPos.x += sqrt(1 + val)*0.00001*spd;
//			camPos.z += sqrt(-val)*0.00001*spd;
//		}
//		else
//		{
//			camPos.x -= sqrt(1 + val)*0.00001*spd;
//			camPos.z -= sqrt(-val)*0.00001*spd;
//		}
//	moveTimer();
}

//void Camera::moveTimer()
//{
//	t_stop = clock();
//	if (float (t_stop - t_start) / CLOCKS_PER_SEC >= 0.2)
//	{
//		t_start = t_stop;
//		nStep = !nStep;
//	}
//}

Vec3 Camera::getRot()
{
	return camRot;
}

Vec3 Camera::getPos()
{
	return camPos;
}


#pragma once
#include "Vec3.h"

#define width glutGet(GLUT_WINDOW_WIDTH) 
#define height glutGet(GLUT_WINDOW_HEIGHT)

class Camera
{
	friend class Player;

public:
	Camera();
	Camera(int);
	~Camera();

	enum camType
	{
		FPP,
		TPP
	}; 
	camType camType;


	float getRot(const char&);
	float getPos(const char&);

private:
	Vec3 camPos;
	Vec3 camRot;
	float camDist;
	bool mMove;
	bool nStep;		//bool for camera movement when moving

	float zoom(Vec3&, const int&);
	void look(const float&, const float&, const Vec3&);
	void look(const Vec3&);
	void camMovement(const float&, const float&);

	void moveTimer();

};


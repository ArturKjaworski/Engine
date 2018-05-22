#pragma once
#include "Vec3.h"

#define width glutGet(GLUT_WINDOW_WIDTH) 
#define height glutGet(GLUT_WINDOW_HEIGHT)

class Camera
{
public:
	Camera();
	Camera(int);
	~Camera();

	Vec3* camPos;
	Vec3* camRot;

	float camDist;
	bool mMove;

	void zoomout(Vec3 v);
	void zoomin(Vec3 v);

	void mouse(const float&, const float&, const Vec3*);
	void keyboard(Vec3& v);

	float getRot(const char&);
	float getPos(const char&);
};


#pragma once


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

	Vec3 getRot();
	Vec3 getPos();

private:
	Vec3 camPos;
	Vec3 camRot;
	float camDist;
	bool mMove;


	float zoom(const int&);
	void look(const float&, const float&, const Vec3&);
	void look(const Vec3&);
};


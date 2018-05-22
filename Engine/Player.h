#pragma once
#include "Vec3.h"
#include "Camera.h"

class Player
{
public:
	Player();
	~Player();

	int hp;
	int stamina;
	int mana;

	Camera* cam;

private:
	Vec3* pos;
	Vec3* rot;
	Vec3* forward;
public:

	void move(const float&, const float&, const float&);
	void look(const float&, const float&);
	void mouse(const float&, const float&);
	void shoot(const Vec3&);

	void onDeath();
	void getHit(int);

	void interact();

	float getRot(const char&);
	float getPos(const char&);

};


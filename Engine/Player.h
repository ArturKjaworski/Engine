#pragma once
#include "Camera.h"

class Player
{
public:
	Player();
	Player(const float&);
	~Player();

	int hp;
	int stamina;
	int mana;
	int speed;

	Camera cam;

private:
	Vec3 pos;
	Vec3 rot;
	Vec3 forward;
	float alpha;
	PxRigidBody* box;

public:
	enum Dir
	{
		front, 
		back, 
		left, 
		right 
	};
	enum stat
	{
		idle,
		walk,
		run,
		swim,      //wrong state, cus can be swim + run = fast swimming etc. ?
		crouch
	}; stat state;

	void move(Dir);
	void look(const float&, const float&);
	void zoom(const char&);
	void mouse(const float&, const float&);

	void shoot(const Vec3&);
	void interact();
	void onDeath();
	void getHit(const int&);

	void setForward();
	void setState(stat);
	void setBox(PxRigidDynamic* actor);

	Vec3 getRot();
	Vec3 getPos();
	Vec3 getforward();
	float getAlpha();
	PxRigidBody* getBox();
};


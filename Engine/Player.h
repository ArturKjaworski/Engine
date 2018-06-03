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
	int speed;

	Camera cam;

	
private:
	Vec3 pos;
	Vec3 rot;
	Vec3 forward;
	float alpha;
	
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
	void setForward();
	void mouse(const float&, const float&);
	void shoot(const Vec3&);
	void zoom(const char&);

	void chState(stat);
	void onDeath();
	void getHit(int&);

	void interact();

	float getRot(const char&);
	float getPos(const char&);
	float getAlpha();
};


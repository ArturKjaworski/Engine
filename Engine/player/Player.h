#pragma once
#include "Camera.h"

class Player
{
public:
	Player(const int& meshId);
	Player(const float& camDist, const int& mesh);
	~Player();

	int hp;
	int stamina;
	int mana;
	int speed;

	Camera* cam;

float idleY = 0;
PxRigidDynamic* actor = nullptr;

private:
	Vec3 rot;
	Vec3 forward;
	float alpha;
	unsigned int ammo;
	
	int model;

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

	//dir: front left right back
	void move(Dir dir);
	
	void look(const float& x, const float& y);
	
	//val: '+', '-'
	void zoom(const char& val);
	void mouse(const float& rotx, const float& roty);

	//v: direction vector (dont need to be normalized)
	void shoot(const Vec3& v);
	void interact();
	void collect();
	float moveTimer();
	void onDeath();
	//val: hp lost
	void getHit(const int& val);

	void setForward();
	//state: idle, walk, run, swim, crouch
	void setState(stat state);
	void setBox(PxRigidDynamic* actor);

	void update();

	Vec3 getRot();
	Vec3 getPos();
	Vec3 getforward();
	float getAlpha();
	int getModel();
	const PxRigidActor* getBox();
};


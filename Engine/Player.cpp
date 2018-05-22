#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	hp = 100;
	stamina = 100;
	mana = 100;

	cam = new Camera();

	pos = new Vec3(0.0,0.0,1.0);
	rot = new Vec3(0,0,NULL);
	forward = new Vec3(0, 0, 1);
}

Player::~Player()
{
	delete(pos);
	delete(rot);
	delete(cam);
}

void Player::move(const float& x, const float& y, const float& z)
{
	pos->x += x;
	pos->y += y;
	pos->z += z;
	
	cam->camPos->x += x;
	cam->camPos->y += y;
	cam->camPos->z += z;
}

void Player::look(const float& x, const float& y)
{
	if (!cam->mMove)
	{
		rot=cam->camRot;
		
		rot->x += x;
		rot->y += y;

		if (rot->x >= 360)
			rot->x = 0;

		if (rot->x <0)
			rot->x = 360;

		if (rot->y >= 70)
			rot->y = 70;

		if (rot->y <-70)
			rot->y = -70;

		cam->mouse(x, y, pos);

		//set new forward vector
		//forward = pos;
		//*forward = *pos - *cam->camPos;
		//cout<< "?"<<forward->x<<endl;
		cam->mMove = true;
	}
	else
		cam->mMove = false;
}

void Player::mouse(const float &rotx, const float& roty)
{
	cam->mouse(rotx, roty, pos);
}

void Player::shoot(const Vec3& v)
{
	//rt
	Vec3 norm = v;
	norm.normalize();

}

void Player::onDeath()
{
	cout << "You Died :)";
}

void Player::getHit(int val)
{
	hp -= val;
	if (hp <= 0)
		onDeath();
}

void Player::interact()
{

}

float Player::getRot(const char &op)
{
	switch (op)
	{
	case 'X': case 'x':
		return rot->x;
		break;
	case 'Y': case 'y':
		return rot->y;
		break;
	}
	return NULL;
}

float Player::getPos(const char &op)
{
	switch (op)
	{
	case 'X': case 'x':
		return pos->x;
		break;

	case 'Y': case 'y':
		return pos->y;

	case 'Z': case 'z':
		return pos->z;
		break;

	}
	return NULL;
}

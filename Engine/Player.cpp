#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	hp = 100;
	stamina = 100;
	mana = 100;

	cam = Camera();

	pos = Vec3();
	rot = Vec3();
	forward = Vec3();

}

Player::~Player()
{

}

void Player::move(Dir dir,const int& speed)
{
	switch (dir)
	{
	case front:
		pos.x += forward.x*speed;
		pos.z += forward.z*speed;
		cam.camPos.x += forward.x*speed;
		cam.camPos.z += forward.z*speed;;
		break;
	case back:
		pos.x -= forward.x*speed;
		pos.z -= forward.z*speed;
		cam.camPos.x -= forward.x*speed;;
		cam.camPos.z -= forward.z*speed;;
		break;
	}

}

void Player::look(const float& x, const float& y)
{
	if (!cam.mMove)
	{
		rot=cam.camRot;
		
		rot.x += x;
		rot.y += y;

		cam.mouse(x, y, pos);
		setForward();

		cout<< "? "<< forward.x<<endl;
		cam.mMove = true;
	}
	else
		cam.mMove = false;
}

void Player::setForward()
{
	//set new forward vector
	forward = pos;
	forward -= cam.camPos;
	forward.normalize();
}

void Player::mouse(const float &rotx, const float& roty)
{
	cam.mouse(rotx, roty, pos);
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
		return rot.x;
		break;
	case 'Y': case 'y':
		return rot.y;
		break;
	}
	return NULL;
}

float Player::getPos(const char &op)
{
	switch (op)
	{
	case 'X': case 'x':
		return pos.x;
		break;

	case 'Y': case 'y':
		return pos.y;

	case 'Z': case 'z':
		return pos.z;
		break;

	}
	return NULL;
}

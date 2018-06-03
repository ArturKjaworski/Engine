#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	hp = 100;
	stamina = 100;
	mana = 100;
	speed = 1;
	state = idle;

	cam = Camera(10);

	pos = Vec3();
	rot = Vec3();
	forward = Vec3();
	alpha = cam.camDist > 4 ? 1 : 0.5;
}

Player::~Player()
{

}

void Player::move(Dir dir)
{
	
	Vec3 v(forward.x, 0, forward.z);
	v.normalize();

	//x^2 + z^2 = 1		 \   (x and z normalized)
	//					  |
	//v.x*x + v.z*z = 0  / 

	float xpow2 = pow(v.z, 2) / (pow(v.z, 2) + pow(v.x, 2));

	switch (dir)
	{
		case front:
		{
			pos += v;
			cam.camPos += v;
			v.x*v.z<0 ? cam.camMovement(xpow2,speed) : cam.camMovement(-xpow2, speed);
			break;
		}

		case back:
		{
			pos -= v;
			cam.camPos -= v;
			v.x*v.z<0 ? cam.camMovement(xpow2, speed) : cam.camMovement(-xpow2, speed);
			break;
		}

		case left:
		{
			//I			
			if (v.z >= 0 && v.x >= 0)
			{
				pos.x += sqrt(xpow2)*speed;
				pos.z -= sqrt(1 - xpow2)*speed;
				cam.camPos.x += sqrt(xpow2)*speed;
				cam.camPos.z -= sqrt(1 - xpow2)*speed;
			}
			//II
			if (v.z >= 0 && v.x < 0)
			{
				pos.x += sqrt(xpow2)*speed;
				pos.z += sqrt(1 - xpow2)*speed;
				cam.camPos.x += sqrt(xpow2)*speed;
				cam.camPos.z += sqrt(1 - xpow2)*speed;
			}
			//III
			if (v.z < 0 && v.x < 0)
			{
				pos.x -= sqrt(xpow2)*speed;
				pos.z += sqrt(1 - xpow2)*speed;
				cam.camPos.x -= sqrt(xpow2)*speed;
				cam.camPos.z += sqrt(1 - xpow2)*speed;
			}
			//IV
			if (v.z < 0 && v.x >= 0)
			{
				pos.x -= sqrt(xpow2)*speed;
				pos.z -= sqrt(1 - xpow2)*speed;
				cam.camPos.x -= sqrt(xpow2)*speed;
				cam.camPos.z -= sqrt(1 - xpow2)*speed;
			}
			break;
		}
	
		case right:
		{
			//I
			if (v.z >= 0 && v.x >= 0)
			{
				pos.x -= sqrt(xpow2)*speed;
				pos.z += sqrt(1 - xpow2)*speed;
				cam.camPos.x -= sqrt(xpow2)*speed;
				cam.camPos.z += sqrt(1 - xpow2)*speed;
			}
			//II
			if (v.z >= 0 && v.x < 0)
			{
				pos.x -= sqrt(xpow2)*speed;
				pos.z -= sqrt(1 - xpow2)*speed;
				cam.camPos.x -= sqrt(xpow2)*speed;
				cam.camPos.z -= sqrt(1 - xpow2)*speed;
			}
			//III
			if (v.z < 0 && v.x < 0)
			{
				pos.x += sqrt(xpow2)*speed;
				pos.z -= sqrt(1 - xpow2)*speed;
				cam.camPos.x += sqrt(xpow2)*speed;
				cam.camPos.z -= sqrt(1 - xpow2)*speed;
			}
			//IV
			if (v.z < 0 && v.x >= 0)
			{
				pos.x += sqrt(xpow2)*speed;
				pos.z += sqrt(1 - xpow2)*speed;
				cam.camPos.x += sqrt(xpow2)*speed;
				cam.camPos.z += sqrt(1 - xpow2)*speed;
			}
			break;
		}
	}
}

void Player::look(const float& x, const float& y)
{
	if (!cam.mMove)
	{
		rot=cam.camRot;
		
		rot.x += x;
		rot.y += y;

		cam.look(x, y, pos);
		setForward();
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
	rot = cam.camRot;

	system("cls");
	cout << speed;
}

void Player::mouse(const float &rotx, const float& roty)
{
	cam.look(rotx, roty, pos);
}

void Player::shoot(const Vec3& v)
{
	//rt
	Vec3 norm = v;
	norm.normalize();

}

void Player::zoom(const char& val)
{
	switch (val)
	{
	case '+':
		alpha = cam.zoom(forward,1);
		break;

	case '-':
		alpha = cam.zoom(forward * -1, -1);
		break;
	}
	cam.look(pos);
}

void Player::chState(stat state)
{
	switch (state)
	{
	case idle:
		state = idle;
		break;
	case walk:
		state = walk;
		if (speed != 1)
			speed = 1;
		break;
		
	case run:
		state = run;
		if (speed != 2)
			speed = 2;
		break;

	case swim:
		state = swim;
		if (speed != 1.75)
			speed = 1.75;
		break;

	case crouch:
		state = crouch;
		if (speed != 1.5)
			speed = 1.5;
		break;
	}
}

void Player::onDeath()
{
	cout << "You Died :)";
}

void Player::getHit(int& val)
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

float Player::getAlpha()
{
	return alpha;
}

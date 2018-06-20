#include "..\stdafx.h"
#include "Player.h"

clock_t t_start = clock();
bool nStep = false;

Player::Player(const int& mesh)
{
	hp = 100;
	stamina = 100;
	mana = 100;
	speed = 1;
	state = idle;

	cam = new Camera(10);
	model = mesh;

	//pos = Vec3();
	rot = Vec3();
	forward = Vec3();
	alpha = cam->camDist > 4 ? 1 : 0.5;
}

Player::Player(const float& camDist, const int& mesh)
{
	hp = 100;
	stamina = 100;
	mana = 100;
	speed = 1;
	state = idle;

	cam = new Camera(camDist);
	model = mesh;

	//pos = Vec3(0, 3, 0);
	rot = Vec3();
	forward = Vec3();
	alpha = cam->camDist > 4 ? 1 : 0.5;
}

Player::~Player()
{
	delete cam;

}

void Player::move(Dir dir)
{
	Vec3 v(forward.x, 0, forward.z);		//delete later
	v.normalize();
	/////////////////////////////
	PxVec3 Pv = PxVec3(v.x, 0, v.z);


	//x^2 + z^2 = 1		 \   (x and z normalized)
	//					  |
	//v.x*x + v.z*z = 0  / 
	PxVec3 newPos = box->getGlobalPose().p;
	float xpow2 = pow(v.z, 2) / (pow(v.z, 2) + pow(v.x, 2));

	switch (dir)
	{
	case front:
	{
		newPos += Pv;
		cam->camPos += v;
		v.x*v.z<0 ? cam->camMovement(xpow2, speed) : cam->camMovement(-xpow2, speed);
		break;
	}

	case back:
	{
		newPos -= Pv;
		cam->camPos -= v;
		v.x*v.z<0 ? cam->camMovement(xpow2, speed) : cam->camMovement(-xpow2, speed);
		break;
	}

	case left:
	{
		//I			
		if (v.z >= 0 && v.x >= 0)
		{
			newPos.x += sqrt(xpow2)*speed;
			newPos.z -= sqrt(1 - xpow2)*speed;
			cam->camPos.x += sqrt(xpow2)*speed;
			cam->camPos.z -= sqrt(1 - xpow2)*speed;
		}
		//II
		if (v.z >= 0 && v.x < 0)
		{
			newPos.x += sqrt(xpow2)*speed;
			newPos.z += sqrt(1 - xpow2)*speed;
			cam->camPos.x += sqrt(xpow2)*speed;
			cam->camPos.z += sqrt(1 - xpow2)*speed;
		}
		//III
		if (v.z < 0 && v.x < 0)
		{
			newPos.x -= sqrt(xpow2)*speed;
			newPos.z += sqrt(1 - xpow2)*speed;
			cam->camPos.x -= sqrt(xpow2)*speed;
			cam->camPos.z += sqrt(1 - xpow2)*speed;
		}
		//IV
		if (v.z < 0 && v.x >= 0)
		{
			newPos.x -= sqrt(xpow2)*speed;
			newPos.z -= sqrt(1 - xpow2)*speed;
			cam->camPos.x -= sqrt(xpow2)*speed;
			cam->camPos.z -= sqrt(1 - xpow2)*speed;
		}
		break;
	}

	case right:
	{
		//I
		if (v.z >= 0 && v.x >= 0)
		{
			newPos.x -= sqrt(xpow2)*speed;
			newPos.z += sqrt(1 - xpow2)*speed;
			cam->camPos.x -= sqrt(xpow2)*speed;
			cam->camPos.z += sqrt(1 - xpow2)*speed;
		}
		//II
		if (v.z >= 0 && v.x < 0)
		{
			newPos.x -= sqrt(xpow2)*speed;
			newPos.z -= sqrt(1 - xpow2)*speed;
			cam->camPos.x -= sqrt(xpow2)*speed;
			cam->camPos.z -= sqrt(1 - xpow2)*speed;
		}
		//III
		if (v.z < 0 && v.x < 0)
		{
			newPos.x += sqrt(xpow2)*speed;
			newPos.z -= sqrt(1 - xpow2)*speed;
			cam->camPos.x += sqrt(xpow2)*speed;
			cam->camPos.z -= sqrt(1 - xpow2)*speed;
		}
		//IV
		if (v.z < 0 && v.x >= 0)
		{
			newPos.x += sqrt(xpow2)*speed;
			newPos.z += sqrt(1 - xpow2)*speed;
			cam->camPos.x += sqrt(xpow2)*speed;
			cam->camPos.z += sqrt(1 - xpow2)*speed;
		}
		break;
	}
	}
	//PxTransform pose(PxVec3(pos.x, pos.y, pos.z), box->getGlobalPose().q);
	PxTransform pose(newPos, box->getGlobalPose().q);
	box->setGlobalPose(pose);
}

void Player::look(const float& x, const float& y)
{
	if (!cam->mMove)
	{
		rot = cam->camRot;
		rot.x += x;
		rot.y -= y;

		PxTransform pose = box->getGlobalPose();
		pose.q = PxQuat((-rot.x)*PI / 180, PxVec3(0, 1, 0));
		box->setGlobalPose(pose);

		cam->look(x, y, Vec3(pose.p.x, pose.p.y, pose.p.z));

		setForward();
		cam->mMove = true;
	}
	else
		cam->mMove = false;
}

void Player::setForward()
{
	//set new forward vector
	forward = Vec3(box->getGlobalPose().p.x, box->getGlobalPose().p.y, box->getGlobalPose().p.z);
	forward -= cam->camPos;
	forward.normalize();
	rot = cam->camRot;
}

void Player::mouse(const float &rotx, const float& roty)
{
	cam->look(rotx, roty, Vec3(box->getGlobalPose().p.x, box->getGlobalPose().p.y, box->getGlobalPose().p.z));
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
		alpha = cam->zoom(1);
		break;

	case '-':
		alpha = cam->zoom(-1);
		break;
	}
	cam->look(Vec3(box->getGlobalPose().p.x, box->getGlobalPose().p.y, box->getGlobalPose().p.z));
	cout << cam->camDist<<endl;
}

void Player::setState(stat state)
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

void Player::setBox(PxRigidDynamic* actor)
{
	box = actor;
}

void Player::onDeath()
{
	cout << "You Died :)";
}

void Player::getHit(const int& val)
{
	hp -= val;
	if (hp <= 0)
		onDeath();
}

void Player::interact()
{

}

#pragma region basic animation timer
float Player::moveTimer()
{
	float tmp_val = (float)(clock() - t_start) / CLOCKS_PER_SEC;
	if (tmp_val >= 0.4)
	{
		t_start = clock();
		nStep = !nStep;
	}

	if (nStep)
		return tmp_val / 12;
	else
		return -tmp_val / 12;

}
#pragma endregion
//CHECK for death AND sync player pos (Vec3) with PhysX pos (PxVec3) (Should be on PxVec3 instead)
void Player::update()
{

	PxTransform pose = box->getGlobalPose();
	//pos.x = pose.p.x;
	//pos.y = pose.p.y;
	//pos.z = pose.p.z;

	idleY += moveTimer();

	if (pose.p.y < -4 || hp <= 0)
	{
		onDeath();
	}
}

Vec3 Player::getRot()
{
	return rot;
}

Vec3 Player::getPos()			//for now... change to PxVec3 in the future
{
	PxVec3 v = box != nullptr ? box->getGlobalPose().p : PxVec3(0, 3, 0);
	return Vec3(v.x, v.y, v.z);
}

Vec3 Player::getforward()
{
	return forward;
}

float Player::getAlpha()
{
	return alpha;
}

int Player::getModel()
{
	return model;
}

PxRigidBody* Player::getBox()
{
	return box;
}

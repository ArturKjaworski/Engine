#include "..\stdafx.h"
#include "Player.h"

clock_t t_start = clock();
bool nStep = false;

Player::Player(const int& mesh)
{
	hp = 100;
	stamina = 100;
	mana = 100;
	ammo = 10;
	speed = 1;
	state = idle;

	cam = new Camera(10);
	model = mesh;

	rot = Vec3();
	forward = Vec3();
	alpha = cam->camDist > 4 ? 1 : 0.5;
}

Player::Player(const float& camDist, const int& mesh)
{
	hp = 100;
	stamina = 100;
	mana = 100;
	ammo = 10;
	speed = 1;
	state = idle;

	cam = new Camera(camDist);
	model = mesh;
	rot = Vec3();
	forward = Vec3();
	alpha = cam->camDist > 4 ? 1 : 0.5;
}

Player::~Player()
{
	if (cam != nullptr)
	{
		delete cam;
		cam = nullptr;
	}
}

void Player::move(Dir dir)
{
	PxVec3 Pv = PxVec3(forward.x, 0, forward.z);
	Pv.normalize();

	//x^2 + z^2 = 1		 }   (x and z normalized)
	//					  }
	//v.x*x + v.z*z = 0  } 
	PxVec3 newPos = actor->getGlobalPose().p;
	float xpow2 = pow(Pv.z, 2) / (pow(Pv.z, 2) + pow(Pv.x, 2));

	switch (dir)
	{
	case front:
	{
		newPos += Pv;
		break;
	}

	case back:
	{
		newPos -= Pv;
		break;
	}

	case left:
	{
		//I			
		if (Pv.z >= 0 && Pv.x >= 0)
		{
			newPos.x += sqrt(xpow2)*speed;
			newPos.z -= sqrt(1 - xpow2)*speed;
		}
		//II
		if (Pv.z >= 0 && Pv.x < 0)
		{
			newPos.x += sqrt(xpow2)*speed;
			newPos.z += sqrt(1 - xpow2)*speed;
		}
		//III
		if (Pv.z < 0 && Pv.x < 0)
		{
			newPos.x -= sqrt(xpow2)*speed;
			newPos.z += sqrt(1 - xpow2)*speed;
		}
		//IV
		if (Pv.z < 0 && Pv.x >= 0)
		{
			newPos.x -= sqrt(xpow2)*speed;
			newPos.z -= sqrt(1 - xpow2)*speed;
		}
		break;
	}

	case right:
	{
		//I
		if (Pv.z >= 0 && Pv.x >= 0)
		{
			newPos.x -= sqrt(xpow2)*speed;
			newPos.z += sqrt(1 - xpow2)*speed;
		}
		//II
		if (Pv.z >= 0 && Pv.x < 0)
		{
			newPos.x -= sqrt(xpow2)*speed;
			newPos.z -= sqrt(1 - xpow2)*speed;
		}
		//III
		if (Pv.z < 0 && Pv.x < 0)
		{
			newPos.x += sqrt(xpow2)*speed;
			newPos.z -= sqrt(1 - xpow2)*speed;
		}
		//IV
		if (Pv.z < 0 && Pv.x >= 0)
		{
			newPos.x += sqrt(xpow2)*speed;
			newPos.z += sqrt(1 - xpow2)*speed;
		}
		break;
	}
	}
	PxTransform pose(newPos, actor->getGlobalPose().q);
	actor->setGlobalPose(pose);
	cam->look(Vec3(newPos.x, newPos.y, newPos.z));
}

void Player::look(const float& x, const float& y)
{
	if (!cam->mMove)
	{
		rot = cam->camRot;
		rot.x += x;
		rot.y -= y;

		PxTransform pose = actor->getGlobalPose();
		pose.q = PxQuat((-rot.x)*PI / 180, PxVec3(0, 1, 0));
		actor->setGlobalPose(pose);

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
	forward = Vec3(actor->getGlobalPose().p.x, actor->getGlobalPose().p.y, actor->getGlobalPose().p.z);
	forward -= cam->camPos;
	forward.normalize();
	rot = cam->camRot;
}

void Player::mouse(const float &rotx, const float& roty)
{
	cam->look(rotx, roty, Vec3(actor->getGlobalPose().p.x, actor->getGlobalPose().p.y, actor->getGlobalPose().p.z));
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
	cam->look(Vec3(actor->getGlobalPose().p.x, actor->getGlobalPose().p.y, actor->getGlobalPose().p.z));
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

void Player::setBox(PxRigidDynamic* _actor)
{
	actor = _actor;
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

void Player::collect()
{
	ammo += 10;
	cout << ammo << endl;
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
	actor->setLinearVelocity(PxVec3(0, 0, 0));
	actor->setMaxAngularVelocity(0);
	//actor->setActorFlag(PxActorFlag::eDISABLE_SIMULATION,true);
	PxTransform pose = actor->getGlobalPose();

	idleY += moveTimer();

	if (pose.p.y < -4 || hp <= 0)
	{
		onDeath();
	}
	if (pose.p.y > 5)
	{
		pose.p.y = 4;
		actor->setGlobalPose(pose);
	}

}

Vec3 Player::getRot()
{
	return rot;
}

Vec3 Player::getPos()			//for now... change to PxVec3 in the future
{
	PxVec3 v = actor != nullptr ? actor->getGlobalPose().p : PxVec3(0, 3, 0);
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

const PxRigidActor* Player::getBox()
{
	return actor;
}

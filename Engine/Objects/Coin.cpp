#include "../stdafx.h"
#include "Coin.h"

Coin::Coin()
{
	name = new string("New Coin");
	amount = 1;
	collected = false;
	pos = Vec3(0, 0, 0);
}

Coin::Coin(const string& _name)
{
	pos = Vec3(0, 0, 0);
	name = new string(_name);
	collected = false;
}

Coin::Coin(const string &_name, const Vec3& _pos, const int & _amount)
{
	*name = _name;
	pos = Vec3(_pos);
	amount = _amount;
	collected = false;
}

Coin::Coin(const float & x, const float & y, const float & z, string name, const int & meshId)
{

}

Coin::Coin(const Vec3 & _pos, const string _name, const int & _meshId)
{
	
	pos = _pos;
	pos.y += 1;
	name = new string(_name);
	model = _meshId;
	collected = false;
	
}

Coin::~Coin()
{
	
}

void Coin::setBox(PxRigidDynamic *actor)
{
	box = actor;
}
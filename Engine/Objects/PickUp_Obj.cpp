#include "../stdafx.h"
#include "PickUp_Obj.h"


PickUp_Obj::PickUp_Obj()
{
	//cout << "PickUp bez par\n";
}

PickUp_Obj::PickUp_Obj(const string& ptr)
{
	name = new string(ptr);
}

PickUp_Obj::PickUp_Obj(const string & _name, const Vec3 & _pos, const int & _amount)
{
	*name = _name;
	pos = Vec3(_pos);
	amount = _amount;
}

PickUp_Obj::PickUp_Obj(const float & x, const float & y, const float & z, const string ptr, const int& meshId)
{
	pos = Vec3(x,y,z);
	name = new string(ptr);
	model = meshId;
}

PickUp_Obj::PickUp_Obj(const Vec3 & vec, const string  ptr, const int& meshId)
{
	//cout << "PickUp z par\n";
	pos = vec;
	name = new string(ptr);
	model = meshId;
}

PickUp_Obj::~PickUp_Obj()
{
//	cout << "desktruktor PickUp\n";
}

void PickUp_Obj::interact()
{
	cout << "\nPickUp interact()\n";
}

//void PickUp_Obj::setBox(PxRigidDynamic *)
//{
//}


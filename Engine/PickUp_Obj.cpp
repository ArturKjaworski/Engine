#include "stdafx.h"
#include "PickUp_Obj.h"


PickUp_Obj::PickUp_Obj()
{
	cout << "PickUp bez par\n";
}

PickUp_Obj::PickUp_Obj(const string ptr)
{
	name = new string(ptr);
}

PickUp_Obj::PickUp_Obj(const float & x, const float & y, const float & z, const string ptr, const int& meshId)
{
	pos = Vec3(x,y,z);
	name = new string(ptr);
	model = meshId;
}

PickUp_Obj::PickUp_Obj(const Vec3 & vec, const string  ptr, const int& meshId)
{
	pos = vec;
	name = new string(ptr);
	model = meshId;
}

PickUp_Obj::~PickUp_Obj()
{
	delete name;
}

void PickUp_Obj::interact()
{
	cout << "\nPickUp interact()\n";
}


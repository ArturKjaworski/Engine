#include "../stdafx.h"
#include "Interactable_Obj.h"


Interactable_Obj::Interactable_Obj()
{
	
}

Interactable_Obj::Interactable_Obj(string ptr) : name(new string(ptr))
{
}

Interactable_Obj::Interactable_Obj(const float & x, const float & y, const float & z, const string ptr, const int& meshId) 
									: pos(Vec3(x,y,z)), name(new string(ptr)), model(meshId)
{
}

Interactable_Obj::Interactable_Obj(const Vec3 & vec, const string ptr, const int& meshId) 
									: pos(vec), name(new string(ptr)), model(meshId)
{
}

Interactable_Obj:: ~Interactable_Obj()
{
		if (name != nullptr)
	{
		delete name;
		name = nullptr;
	}

}

void Interactable_Obj::interact()
{
	

}
const string Interactable_Obj::getName() 
{
	return *name;
}

PxRigidDynamic * Interactable_Obj::getBox()
{
	return box;
}

int Interactable_Obj::getModel()
{
	return model;
}

void Interactable_Obj::setBox(PxRigidDynamic *actor)
{
	box = actor;
}
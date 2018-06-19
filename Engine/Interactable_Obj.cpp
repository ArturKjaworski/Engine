#include "stdafx.h"
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
	delete name;
}

void Interactable_Obj::interact()
{
	cout << "\nInteractable_Obj interact()\n";

}
const string Interactable_Obj::getName() 
{
	return *name;
}

PxRigidBody * Interactable_Obj::getBox()
{
	return box;
}

int Interactable_Obj::getModel()
{
	return model;
}

void Interactable_Obj::setBox(PxRigidBody *actor)
{
	box = actor;
}
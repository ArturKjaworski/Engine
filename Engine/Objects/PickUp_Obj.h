#pragma once
#include "Interactable_Obj.h"
class PickUp_Obj :	public Interactable_Obj
{
public:
	PickUp_Obj();
	PickUp_Obj(const string& name);
	PickUp_Obj(const string& name, const Vec3& pos, const int& amount);
	PickUp_Obj(const float& x, const float& y, const float& z, string name, const int&meshId);
	PickUp_Obj(const Vec3& pos, const string name,const int&meshId);
	
	virtual ~PickUp_Obj();
	int amount;
	
public:
	void interact() override;
//	virtual void setBox(PxRigidDynamic*) override;

};
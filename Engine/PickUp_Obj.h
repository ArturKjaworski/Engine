#pragma once
#include "Interactable_Obj.h"
class PickUp_Obj :	public Interactable_Obj
{
public:
	PickUp_Obj();
	PickUp_Obj(const string);
	PickUp_Obj(const float&, const float&, const float&, string, const int&);
	PickUp_Obj(const Vec3&, const string,const int&);
	~PickUp_Obj();
	int amount;
	
public:
	void interact() override;


};


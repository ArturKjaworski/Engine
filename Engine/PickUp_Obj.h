#pragma once
#include "Interactable_Obj.h"
class PickUp_Obj :	public Interactable_Obj
{
public:
	int amount;

	PickUp_Obj();
	PickUp_Obj(string);

	virtual void interact() override;
};


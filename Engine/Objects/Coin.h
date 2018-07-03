#pragma once
#include "PickUp_Obj.h"

class Coin : public PickUp_Obj
{
public:
	Coin();
	Coin(const string& name);
	Coin(const string& name, const Vec3& pos, const int& amount);
	Coin(const float& x, const float& y, const float& z, string name, const int& meshId);
	Coin(const Vec3& pos, const string name, const int& meshId);
	~Coin();
	
	

	void setBox(PxRigidDynamic*) override;
};


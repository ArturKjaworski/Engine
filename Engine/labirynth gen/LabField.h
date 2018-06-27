#pragma once
#include "../objects/Coin.h"
class LabField
{
	friend class LabGen;
public:
	LabField();
	LabField(const Vec3& pos);
	~LabField();
	static int size;

	vector<PxRigidStatic*> walls;
private:
	Vec3 pos;

	//Walls
	bool n;
	bool e;
	bool w;
	bool s;

	bool used;

	void setWall(PxRigidStatic* actor);
};
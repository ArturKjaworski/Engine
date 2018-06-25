#pragma once
class LabField
{
	friend class LabGen;
public:
	LabField();
	LabField(const Vec3&);
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
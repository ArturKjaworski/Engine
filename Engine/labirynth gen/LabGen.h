#pragma once
#include "LabField.h"
#include <vector>

class LabGen
{
public:
	LabGen();
	LabGen(const Vec3&);
	LabGen(const float& sizeX, const float& sizeZ);
	~LabGen();

	void setWall(PxRigidStatic *(*createStatic)(const PxVec3 &, const float &, const PxVec3 &, const PxGeometry &));

	void render();
	int getSize();
	//ii: field number
	Vec3 getF_pos(const int& ii);
private:
	Vec3 pos;
	vector<LabField> field;
	Vec3 size;
	void init();
	//start: starting point in the array, most of the time 0
	void setWall(const int& start);
	void optWalls();
};
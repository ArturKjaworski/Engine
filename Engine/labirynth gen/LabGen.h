#pragma once
#include "../Vec3.h"
#include "LabField.h"
#include <vector>

class LabGen
{
public:
	LabGen();
	LabGen(const Vec3&);
	LabGen(const float& sizeX, const float& sizeZ);
	~LabGen();

	void SetWalls(PxRigidStatic *(*createStatic)(const PxVec3 &, const float &, const PxVec3 &, const PxGeometry &));

	void render();

private:
	Vec3 pos;
	vector<LabField> field;
	Vec3 size;
	void initialize();
	void setWalls(const int&);
	void optWalls();
};


#include "../stdafx.h"
#include "LabField.h"

int LabField::size=20;

LabField::LabField()
{
	pos = Vec3(0, 0, 0);
	n = true;
	e = true;
	w = true;
	s = true;
	used = false;
}

LabField::LabField(const Vec3& _pos) : pos(_pos)
{
	n = true;
	e = true;
	w = true;
	s = true;
	used = false;
}

LabField::~LabField()
{
	walls.clear();
}

void LabField::setWall(PxRigidStatic * actor)
{
	walls.push_back(actor);
}





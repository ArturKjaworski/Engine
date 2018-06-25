#include "stdafx.h"
#include "LabField.h"

int LabField::size=20;

LabField::LabField()
{
}

LabField::LabField(const Vec3& nPos) : pos(nPos)
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





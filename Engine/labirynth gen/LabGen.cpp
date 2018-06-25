#include "../stdafx.h"
#include "LabGen.h"

LabGen::LabGen()
{
}

//can be filled as: Vec3(x,z,0) OR Vec3(x,0,z) 
LabGen::LabGen(const Vec3& v)
{
	size = v.y != 0 ? Vec3(v.x, 0, v.y) : Vec3(v.x, 0, v.z);
	initialize();
}

//params: size X, size Z
LabGen::LabGen(const float &sizeX, const float &sizeZ)
{
	size = Vec3(sizeX, 0, sizeZ);
	initialize();
}

LabGen::~LabGen()
{
	field.clear();
}

void LabGen::initialize()
{
	int tmp = 0;

	field.push_back(LabField(Vec3(0, pos.y, 0)));
	for (int ii = 1; ii < size.x * size.z; ++ii)
	{
		if ((ii% int(size.x)) == 0)
		{
			++tmp;
			field.push_back(LabField(Vec3(field[0].pos.x, pos.y, tmp * LabField::size)));
		}
		else
			field.push_back(LabField(Vec3( field[(ii%int(size.x))-1].pos.x + LabField::size, pos.y , tmp * LabField::size)));
	}

	setWalls(0);
	optWalls();
}

void LabGen::SetWalls(PxRigidStatic* (*createStatic)(const PxVec3&, const float&, const PxVec3&, const PxGeometry&))
{
	for (int ii = 0; ii < field.size(); ii++)
	{
		if (field[ii].n)
			field[ii].setWall(createStatic(PxVec3(field[ii].pos.x , field[ii].pos.y, field[ii].pos.z - LabField::size / 2), 0, PxVec3(0, 0, 0), PxBoxGeometry(10, LabField::size / 2, 1)));

		if (field[ii].s)
			field[ii].setWall(createStatic(PxVec3(field[ii].pos.x, field[ii].pos.y, field[ii].pos.z + LabField::size / 2), 0, PxVec3(0, 0, 0), PxBoxGeometry(10, LabField::size / 2, 1))); 
		
		if (field[ii].e)
			field[ii].setWall(createStatic(PxVec3(field[ii].pos.x - LabField::size / 2, field[ii].pos.y, field[ii].pos.z), 0, PxVec3(0, 0, 0), PxBoxGeometry(1, LabField::size / 2, 10)));
	
		if (field[ii].w)
			field[ii].setWall(createStatic(PxVec3(field[ii].pos.x + LabField::size / 2, field[ii].pos.y, field[ii].pos.z), 0, PxVec3(0, 0, 0), PxBoxGeometry(1, LabField::size / 2, 10)));
	}
}

void LabGen::render()
{
	for (int i = 0; i<size.x*size.z; i++)
	{
		//N sciana
		
		glColor3f(0.5, 0.5, 0.5);
		if (field[i].n == true) {
			glBegin(GL_QUADS);
			glVertex3f(field[i].pos.x - field[i].LabField::size / 2, 0, field[i].pos.z - field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x + field[i].LabField::size / 2, 0, field[i].pos.z - field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x + field[i].LabField::size / 2, LabField::size, field[i].pos.z - field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x - field[i].LabField::size / 2, LabField::size, field[i].pos.z - field[i].LabField::size / 2);
			glEnd();
		}
		//s sciana
		//
		if (field[i].s == true) {
			glBegin(GL_QUADS);
			glVertex3f(field[i].pos.x - field[i].LabField::size / 2, 0, field[i].pos.z + field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x + field[i].LabField::size / 2, 0, field[i].pos.z + field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x + field[i].LabField::size / 2, LabField::size, field[i].pos.z + field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x - field[i].LabField::size / 2, LabField::size, field[i].pos.z + field[i].LabField::size / 2);
			glEnd();
		}
		//e sciana

		if (field[i].e == true) {
			glBegin(GL_QUADS);
			glVertex3f(field[i].pos.x - field[i].LabField::size / 2, 0, field[i].pos.z - field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x - field[i].LabField::size / 2, 0, field[i].pos.z + field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x - field[i].LabField::size / 2, LabField::size, field[i].pos.z + field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x - field[i].LabField::size / 2, LabField::size, field[i].pos.z - field[i].LabField::size / 2);
			glEnd();
		}
		//w sciana

		if (field[i].w == true) {
			glBegin(GL_QUADS);
			glVertex3f(field[i].pos.x + field[i].LabField::size / 2, 0, field[i].pos.z - field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x + field[i].LabField::size / 2, 0, field[i].pos.z + field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x + field[i].LabField::size / 2, LabField::size, field[i].pos.z + field[i].LabField::size / 2);
			glVertex3f(field[i].pos.x + field[i].LabField::size / 2, LabField::size, field[i].pos.z - field[i].LabField::size / 2);
			glEnd();
		}
	}
}

//WEST AND EAST ARE SWAPPED!! (Mistakes were made...) 
//It sets "virtual" walls
void LabGen::setWalls(const int& i=0)
{
	while (true)
	{
		int tmp = rand() % 4;

		//WEST
		if (tmp == 0)
		{
			if (((i + 1) % int(size.x)) != 0) 
			{
				if ((field[i + 1].n == true) && (field[i + 1].e == true) && (field[i + 1].w == true) && (field[i + 1].s == true))
				{
					field[i].used = true;
					field[i].w = false;
					field[i + 1].e = false;
					setWalls(i + 1);
				}
			}
		}
		//SOUTH 
		if (tmp == 1)
		{
			if ((i + int(size.x)) < (int(size.x)*int(size.z)))
			{
				if ((field[i + int(size.x)].n == true) && (field[i + int(size.x)].e == true) && (field[i + int(size.x)].w == true) && (field[i + int(size.x)].s == true))
				{
					field[i].used = true;
					field[i].s = false;
					field[i + int(size.x)].n = false;
					setWalls(i + int(size.x));
				}
			}
		}
		//NORTH
		if (tmp == 2)
		{
			if ((i - int(size.x)) >= 0)
			{
				if ((field[i - int(size.x)].n == true) && (field[i - int(size.x)].e == true) && (field[i - int(size.x)].w == true) && (field[i - int(size.x)].s == true))
				{
					field[i].used = true;
					field[i].n = false;
					field[i - int(size.x)].s = false;
					setWalls(i - int(size.x));
				}
			}
		}
		//EAST
		if (tmp == 3)
		{
			if ((i%int(size.x)) != 0)
			{
				if ((field[i - 1].n == true) && (field[i - 1].e == true) && (field[i - 1].w == true) && (field[i - 1].s == true))
				{
					field[i].used = true;

					field[i].e = false;
					field[i - 1].w = false;
					setWalls(i - 1);

				}
			}
		}

		if (((i + 1) % int(size.x) == 0 || field[i + 1].used)
			&& ((i%int(size.x)) == 0 || field[i - 1].used)
			&& ((i - int(size.x))<0 || field[i - int(size.x)].used)
			&& ((i + int(size.x)) >= int(size.x)*int(size.z) || field[i + int(size.x)].used))
		{
			field[i].used = true;
			break;
		}
	}
}

//OPTIMIZE and CREATE walls
void LabGen::optWalls()
{
	for (int ii = 0; ii < field.size(); ii++)
	{
		if (field[ii].n && ((ii - size.x)>0) && field[ii - (int)size.x].s)
		{
			field[ii].n = false;
		}

		if (field[ii].e && (ii % (int)size.x != 0) && field[ii - 1].w)
		{
			field[ii].e = false;
		}

		if (field[ii].w && ((ii + 1) % (int)size.x != 0) && field[ii + 1].e)
		{
			field[ii].w = false;
		}

		if (field[ii].s && ((ii + (int)size.x)<(int)size.x*(int)size.z) && field[ii + (int)size.x].n)
		{
			field[ii].s = false;
		}
	}
}

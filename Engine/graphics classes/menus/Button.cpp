#include "stdafx.h"
#include "Button.h"


Button::Button(const Vec3& _pos, const Vec3& _size, const string& _name) : pos(_pos), size(_size), name(_name)
{
	active = false;
}

Button::~Button()
{
}

bool Button::onPointer(const int& x, const int& y)
{
	if ((x > pos.x && x < pos.x + size.x) && (y > pos.y && y < pos.y + size.y))
	{
		active = true;
		return true;
	}
	else
		return false;
}

bool Button::onClick(const int& x, const int& y)
{
	if (onPointer(x, y))
	{
		return true; //use proper function
	}
	else return false;
}

void Button::render()
{
	if (active)
		glColor3f(0.5, 0.5, 0.5);
	else
		glColor3f(0.2, 0.2, 0.2);

	glBegin(GL_QUADS);
		glVertex3f(pos.x, pos.y, -1);
		glVertex3f(pos.x+size.x,pos.y, -1);
		glVertex3f(pos.x+size.x, pos.y + size.y, -1);
		glVertex3f(pos.x, pos.y + size.y, -1);
	glEnd();
}

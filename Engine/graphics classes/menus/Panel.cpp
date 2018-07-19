#include "stdafx.h"
#include "Panel.h"


Panel::Panel()
{
}

Panel::~Panel()
{
	for (int ii = 0; ii < buttons.size(); ++ii)
		delete(buttons[ii]);
	buttons.clear();
}


void Panel::render(const int & _w, const int & _h)
{
}

void Panel::printw(float x, float y, float z, string format)
{
	glRasterPos3f(x, y, z);

	for (int i = 0; format[i] != '\0'; i++)
		glutBitmapCharacter(font_style, format[i]);

}
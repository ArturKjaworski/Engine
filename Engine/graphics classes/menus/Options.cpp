#include "stdafx.h"
#include "Options.h"


Options::Options(const string & _name, const int & _w, const int & _h)
{
	crButton(_w, _h);
}

Options::~Options()
{
}

void Options::crButton(const int & _w, const int & _h)
{
	buttons.push_back(new Button(Vec3(0.05*_w - 5, _h - (_h / 2 * 0.3) - 5, -1), Vec3(110, 24, 0), "Options"));

	buttons[0]->active = true;
}

void Options::render(const int & _w, const int & _h)
{
	glColor4f(1, 1, 1, 1);
	printw(0.05*_w, _h - (_h / 2 * 0.3), -1, "esc to menu");


	for (int ii = 0; ii<buttons.size(); ++ii)
		buttons[ii]->render();
}

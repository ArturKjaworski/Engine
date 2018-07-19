#include "stdafx.h"
#include "Credits.h"


Credits::Credits(const string & _name, const int & _w, const int & _h)
{
	name = _name;
}

Credits::~Credits()
{
}

void Credits::crButton(const int & _w, const int & _h)
{
}

void Credits::render(const int & _w, const int & _h)
{
	glColor4f(1, 1, 1, 1);
	printw(0.6*_w, _h - (_h / 2 * 0.3), -1, "Created by:");
	printw(0.59*_w, _h - (_h / 2 * 0.3) - 90, -1, "Artur Jaworski");
}

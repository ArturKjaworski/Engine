#include "stdafx.h"
#include "HowTo.h"


HowTo::HowTo(const string & _name, const int & _w, const int & _h)
{
	name = _name;
}

HowTo::~HowTo()
{
}

void HowTo::crButton(const int & _w, const int & _h)
{
}

void HowTo::render(const int & _w, const int & _h)
{
	glColor4f(1, 1, 1, 1);
	printw(0.6*_w, _h - (_h / 2 * 0.3), -1, "How to play");
	printw(0.5*_w, _h - (_h / 2 * 0.35) - 45, -1, "10 points for every killed opponent");
	printw(0.51*_w, _h - (_h / 2 * 0.35) - 70, -1, "5 points for every ammo colected");
	printw(0.52*_w, _h - (_h / 2 * 0.35) - 95, -1, "Collect all ammo to finish game");

	printw(0.62*_w, _h - (_h / 2 * 0.9), -1, "Control");
	printw(0.3*_w, _h - (_h / 2 * 0.9) - 45, -1, "Keyboard");
	printw(0.3*_w, _h - (_h / 2 * 0.9) - 90, -1, "W, S, A, D - movement");
	printw(0.3*_w, _h - (_h / 2 * 0.9) - 115, -1, "Z, X - zoom in/out");
	printw(0.3*_w, _h - (_h / 2 * 0.9) - 140, -1, "ESC - pause/exit");

	printw(0.3*_w, _h - (_h / 2 * 0.9) - 185, -1, "Mouse");
	printw(0.3*_w, _h - (_h / 2 * 0.9) - 230, -1, "No button pressed - changing direction of movement");
	printw(0.3*_w, _h - (_h / 2 * 0.9) - 255, -1, "RMB pressed - look around without changing movement direction");
	printw(0.3*_w, _h - (_h / 2 * 0.9) - 280, -1, "LPM - attack");
}

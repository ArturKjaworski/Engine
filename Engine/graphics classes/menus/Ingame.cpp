#include "stdafx.h"
#include "Ingame.h"


Ingame::Ingame(const string & _name, const int & _w, const int & _h)
{
	name = _name;

}

Ingame::~Ingame()
{
}

void Ingame::crButton(const int & _w, const int & _h)
{
}

void Ingame::render(const int & _w, const int & _h, const int& score, const int& ammo, const int& hp)
{
	glColor4f(1, 0, 0, 1);
	printw(0.05*_w, (_h / 2 * 0.3) - 45, -1, "Score: " + to_string(score));
	printw(0.85*_w, (_h / 2 * 0.3 + 35) - 45, -1, "Ammo: " + to_string(ammo));
	printw(0.85*_w, (_h / 2 * 0.3) - 45, -1, "HP: " + to_string(hp));
}

void Ingame::render(const int & _w, const int & _h)
{
}

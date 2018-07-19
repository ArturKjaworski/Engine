#include "stdafx.h"
#include "PauseMenu.h"


PauseMenu::PauseMenu(const string & _name, const int & _w, const int & _h)
{
	name = _name;
	crButton(_w, _h);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::crButton(const int & _w, const int & _h)
{
	buttons.push_back(new Button(Vec3(0.47*_w - 5, _h - (_h / 2) + 30 - 5, -1), Vec3(110, 24, 0), "Continue"));
	buttons.push_back(new Button(Vec3(0.47*_w - 5, _h - (_h / 2) - 15 - 5, -1), Vec3(110, 24, 0), "Exit to menu"));
	buttons[0]->active = true;
}

void PauseMenu::render(const int & _w, const int & _h)
{
	glColor3f(1, 1, 1);
	printw(0.47*_w, _h - (_h / 2) + 90, -1, "Game paused");
	printw(0.49*_w, _h - (_h / 2) + 30, -1, "Continue");
	printw(0.47*_w, _h - (_h / 2) - 15, -1, "Exit to Menu");

	for (int ii = 0; ii<buttons.size(); ++ii)
		buttons[ii]->render();
}

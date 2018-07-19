#include "stdafx.h"
#include "Menu.h"



Menu::Menu(const string& _name, const int& _w, const int& _h)
{
	name = _name;
	crButton(_w, _h);
}

void Menu::crButton(const int& _w, const int& _h)
{
	buttons.push_back(new Button(Vec3(0.05*_w-5, _h - (_h / 2 * 0.3)-5, -1), Vec3(110, 24, 0), "New Game"));
	buttons.push_back(new Button(Vec3(0.05*_w-5, _h - (_h / 2 * 0.3) - 45-5, -1), Vec3(110, 24, 0), "How to play"));
	buttons.push_back(new Button(Vec3(0.05*_w -5, _h - (_h / 2 * 0.3) - 90 - 5, -1), Vec3(110, 24, 0), "HighScore"));
	buttons.push_back(new Button(Vec3(0.05*_w - 5, _h - (_h / 2 * 0.3) - 135-5, -1), Vec3(110, 24, 0), "Options"));
	buttons.push_back(new Button(Vec3(0.05*_w - 5, (_h / 2 * 0.3)-5, -1), Vec3(110, 24, 0), "Credits"));
	buttons.push_back(new Button(Vec3(0.05*_w - 5, (_h / 2 * 0.3) - 45-5, -1), Vec3(110, 24, 0), "Exit"));
	buttons[0]->active = true;
}

Menu::~Menu()
{
}

void Menu::render(const int& _w, const int& _h)
{
	glColor4f(1, 1, 1, 1);
	printw(0.05*_w, _h - (_h / 2 * 0.3), -1, "New Game");
	printw(0.05*_w, _h - (_h / 2 * 0.3) - 45, -1, "How to play");
	printw(0.05*_w, _h - (_h / 2 * 0.3) - 90, -1, "HighScore");
	printw(0.05*_w, _h - (_h / 2 * 0.3) - 135, -1, "Options");
	printw(0.05*_w, (_h / 2 * 0.3), -1, "Credits");
	printw(0.05*_w, (_h / 2 * 0.3) - 45, -1, "Exit");

	for (int ii=0;ii<buttons.size();++ii)
		buttons[ii]->render();
}
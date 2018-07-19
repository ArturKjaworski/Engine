#pragma once
#include "Panel.h"
class Ingame :
	public Panel
{
public:
	Ingame(const string & _name, const int& _w, const int& _h);
	~Ingame();

	void crButton(const int& _w, const int& _h)override;
	void render(const int & _w, const int & _h, const int & score, const int & ammo, const int & hp);
	void render(const int& _w, const int& _h)override;
};


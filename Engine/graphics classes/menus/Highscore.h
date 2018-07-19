#pragma once
#include "Panel.h"
class Highscore :
	public Panel
{
public:
	Highscore(const string & _name, const int& _w, const int& _h);
	~Highscore();

	void crButton(const int& _w, const int& _h)override;
	void render(const int& _w, const int& _h)override;
};


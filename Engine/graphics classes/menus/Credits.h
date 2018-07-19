#pragma once
#include "Panel.h"
class Credits :public Panel
{
public:
	Credits(const string & _name, const int& _w, const int& _h);
	~Credits();

	void crButton(const int& _w, const int& _h)override;
	void render(const int& _w, const int& _h)override;
};


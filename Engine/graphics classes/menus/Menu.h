#pragma once
#include "Panel.h"
#include "Options.h"
class Menu : public Panel
{
public:
	Menu(const string & _name, const int& _w, const int& _h);
	void crButton(const int& _w, const int& _h)override;
	~Menu();

	void render(const int& _w, const int& _h)override;

};
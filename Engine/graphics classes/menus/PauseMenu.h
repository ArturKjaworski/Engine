#pragma once
#include "Panel.h"
class PauseMenu : public Panel
{
public:
	PauseMenu(const string & _name, const int& _w, const int& _h);
	~PauseMenu();

	void crButton(const int& _w, const int& _h)override;
	void render(const int& _w, const int& _h)override;
};


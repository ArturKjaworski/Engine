#pragma once
#include "Panel.h"
class HowTo :
	public Panel
{
public:
	HowTo(const string & _name, const int& _w, const int& _h);
	~HowTo();

	void crButton(const int& _w, const int& _h)override;
	void render(const int& _w, const int& _h)override;
};


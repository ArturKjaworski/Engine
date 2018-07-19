#pragma once
#include "Panel.h"
class Options :
	public Panel

{
public:
	Options(const string & _name, const int& _w, const int& _h);
	~Options();

	void crButton(const int& _w, const int& _h)override;
	void render(const int& _w, const int& _h)override;
};


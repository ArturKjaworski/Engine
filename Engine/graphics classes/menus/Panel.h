#pragma once
#include "button.h"
class Panel
{
public:
	Panel();
	virtual ~Panel();

	string name;
	vector<Button*> buttons;

protected:
	virtual void crButton(const int& _w, const int& _h) = 0;
	virtual void render(const int& _w, const int& _h)=0;

	GLvoid * font_style = GLUT_BITMAP_HELVETICA_18;
	virtual void printw(float x, float y, float z, string format);
};


#include "stdafx.h"
#include "Highscore.h"


Highscore::Highscore(const string & _name, const int & _w, const int & _h)
{
	name = _name;

}

Highscore::~Highscore()
{
}

void Highscore::crButton(const int & _w, const int & _h)
{
}

void Highscore::render(const int & _w, const int & _h)
{
	glColor4f(1, 1, 1, 1);
	//odczytaj z notatnika highscore
	printw(0.6*_w, _h - (_h / 2 * 0.3), -1, "HighScore");

	for (int ii = 1; ii <= 10; ++ii)
		printw(0.3*_w, _h - (_h / 2 * 0.3) - (ii) * 45, -1, to_string(ii) + ". ");
}

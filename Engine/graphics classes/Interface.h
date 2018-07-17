#pragma once
#include "..\Game.h"

class Interface
{
public:
	Interface();
	~Interface();

	//window size
	int _w, _h;

#pragma region Game class
	Game* game = nullptr;
#pragma endregion

	struct gameState
	{
		enum Enum
		{
			menu,
			howTo,
			highscore,
			options,
			credits,
			pauseMenu,
			running
		};
	};

	//for esc only (go to previous window)
	void goBack();
	//set UI to chosen option (forward)
	void goNext();
	//update UI (set current UI)
	void update();

	void UIinit();
	void UIcleanUp();

	//get current state of UI (e.g. highscore)
	int getState();

	//pre
	Interface& operator++();
	Interface& operator--();
	//post
	Interface operator++(int);
	Interface operator--(int);


private:
	//current state of UI (e.g. highscore)
	uint8_t state;
	//current chosen option in UI (to accept that option use goNext())
	uint8_t select;

	void menu();
	void newGame();
	void howTo();
	void highscore();
	void options();
	void credits();
	void pauseMenu();
	void running();

	GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
	void printw(float x, float y, float z, string format);

};
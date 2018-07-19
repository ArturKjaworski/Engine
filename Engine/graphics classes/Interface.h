#pragma once
#include "..\Game.h"
#include "menus\Menu.h"
#include "menus\Options.h"
#include "menus\PauseMenu.h"
#include "menus\HowTo.h"
#include "menus\Highscore.h"
#include "menus\Credits.h"
#include "menus\Ingame.h"
class Interface
{
public:
	Interface();
	~Interface();

	//window size
	int _w = glutGet(GLUT_WINDOW_WIDTH);
	int _h = glutGet(GLUT_WINDOW_HEIGHT);

	Game* game = nullptr;

#pragma region UI vars
	Menu* menu;
	Options* options = nullptr;
	PauseMenu* pauseMenu = nullptr;
	HowTo* howTo = nullptr;
	Highscore* highscore = nullptr;
	Credits* credits = nullptr;
	Ingame* inGame = nullptr;
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

	//on mouse overlap
	void mouse(const int& x, const int& y);
	//on mouse click
	void mouseClick(const int & x, const int & y);

	//update UI (set current UI)
	void update();

	//get current state of UI (e.g. highscore)
	int getState();

#pragma region op overload
	//pre
	Interface& operator++();
	Interface& operator--();
	//post
	Interface operator++(int);
	Interface operator--(int);
#pragma endregion

private:
	//current state of UI (e.g. highscore)
	uint8_t state;
	//current chosen option in UI (to accept that option use goNext())
	uint8_t select;

	void UIinit();
	void UIcleanUp();
	void buttonClear(int i);

	void newGame();
	void gameCleanup();

	GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
};
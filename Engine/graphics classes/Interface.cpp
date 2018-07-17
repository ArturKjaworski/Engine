#include "../stdafx.h"
#include "Interface.h"


	Interface::Interface() : state(gameState::menu), select(0){}

	Interface::~Interface() 
	{
		if (game != nullptr)
		{
			delete game;
			game = nullptr;
		}
	}

	void Interface::goBack()
	{
		//for esc
		switch (state)
		{
			case Interface::gameState::menu:
			case Interface::gameState::highscore:
			case Interface::gameState::credits:
			{
				exit(0);
			}

			case Interface::gameState::pauseMenu:
			{

				state = gameState::running;
				
				ShowCursor(false);
				break;
			}

			case Interface::gameState::running:
			{
				state = gameState::pauseMenu; 
				ShowCursor(true);
				break;
			}

			case Interface::gameState::options:
			{
			//options: accept back
				state = gameState::menu;
				break;
			}
		}
	}

	void Interface::goNext()
	{
		switch (state)
		{
			case gameState::menu:
			case gameState::highscore:
			case gameState::credits:
			case gameState::howTo:
			{
				switch (select)
				{
				case 0:
					newGame();
					state = gameState::running;
					break;

				case 1:
					state = gameState::howTo;
					break;

				case 2:
					state = gameState::highscore;
					break;

				case 3:
					state = gameState::options;
					break;

				case 4:
					state = gameState::credits;
					break;
				case 5:
					exit(0);
					break;
				}
				break;
			}

			case gameState::options:
			{
				select = 0;
				//same as 
				break;
			}
			case gameState::running:
			{
				//minimap?
				break;
			}
			case gameState::pauseMenu:
			{
				if (select  == 0)
					state = gameState::running;
				else 
				{
					state = gameState::menu;
					ShowCursor(false);
				}
				select = 0;
			}
		}
	}

	void Interface::update()
	{
		_w = glutGet(GLUT_WINDOW_WIDTH);
		_h = glutGet(GLUT_WINDOW_HEIGHT);
		
		 UIinit();

		switch (state)
		{
		
			case gameState::menu:
			{
				menu();
				break;
			}
			case gameState::howTo:
			{
				menu();
				howTo();
				break;
			}
			case gameState::highscore:
			{
				menu();
				highscore();
				break;
			}
			case gameState::credits:
			{
				menu();
				credits();
				break;
			}
			case gameState::options:
			{
				menu();
				options();
				break;
			}
			case gameState::pauseMenu:
			{
				pauseMenu();
				break;
			}
			case gameState::running:
			{
				if (game != nullptr && getState() == gameState::running)
				{
					running();
					UIcleanUp();

					glEnable(GL_LIGHTING);
					game->update();
					glDisable(GL_LIGHTING);
				}
				break;
			}
		}
	}

	#pragma region UI enable/disable
	void Interface::UIinit()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, _w, 0.0f, _h, 0.1f, 1000);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0, 0.0, 0.0, 0.5);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glDisable(GL_TEXTURE_2D);
	}
	void Interface::UIcleanUp()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (GLdouble)_w / (GLdouble)_h, 0.1f, 1000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
	}
#pragma endregion

	#pragma region GUI
	void Interface::menu()
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);

		if (state != Interface::gameState::options)
		{
			if (select == 255)
				select = 5;
			else if (select > 5)
				select = 0;

			if (select < 4)
				printw(0.05*_w, _h - (_h / 2 * 0.3) - 5 - (45 * select), -1, "___________");
			else
				printw(0.05*_w, _h - (_h / 2 * 0.3) - 5 - (45 * (select + 6)), -1, "___________");
		}
		printw(0.05*_w, _h-(_h/2*0.3), -1, "New Game");
		printw(0.05*_w, _h-(_h/2*0.3)-45, -1, "How to play");
		printw(0.05*_w, _h - (_h / 2 * 0.3) -90, -1, "HighScore");
		printw(0.05*_w, _h - (_h / 2 * 0.3) -135, -1, "Options");
		printw(0.05*_w, (_h / 2 * 0.3) , -1, "Credits");
		printw(0.05*_w, (_h / 2 * 0.3) -45, -1, "Exit");
	}

	void Interface::newGame()
	{
		if (game == nullptr)
			game = new Game();
		else
		{
			delete game;
			game = nullptr;
			game = new Game();
			
		}
		ShowCursor(false);
		select = 0;
		glutWarpPointer(_w / 2, _h / 2);
	}

	void Interface::running()
	{
		glColor4f(1, 0, 0, 1);
		printw(0.05*_w, (_h / 2 * 0.3) - 45, -1, "Score: " + to_string(game->player->score));
		printw(0.9*_w, (_h / 2 * 0.3+35) - 45, -1, "Ammo: " + to_string(game->player->ammo));
		printw(0.9*_w, (_h / 2 * 0.3) - 45, -1, "HP: " + to_string(game->player->hp));
	}

	void Interface::howTo()
	{
		printw(0.6*_w, _h - (_h / 2 * 0.3), -1, "How to play");
		printw(0.5*_w, _h - (_h / 2 * 0.35) - 45, -1, "10 points for every killed opponent");
		printw(0.51*_w, _h - (_h / 2 * 0.35) - 70, -1, "5 points for every ammo colected");
		printw(0.52*_w, _h - (_h / 2 * 0.35) - 95, -1, "Collect all ammo to finish game");

		printw(0.62*_w, _h - (_h / 2 * 0.9), -1, "Control");
		printw(0.3*_w, _h - (_h / 2 * 0.9) - 45, -1, "Keyboard");
		printw(0.3*_w, _h - (_h / 2 * 0.9) - 90, -1, "W, S, A, D - movement");
		printw(0.3*_w, _h - (_h / 2 * 0.9) - 115, -1, "Z, X - zoom in/out");
		printw(0.3*_w, _h - (_h / 2 * 0.9) - 140, -1, "ESC - pause/exit");

		printw(0.3*_w, _h - (_h / 2 * 0.9) - 185, -1, "Mouse");
		printw(0.3*_w, _h - (_h / 2 * 0.9) - 230, -1, "No button pressed - changing direction of movement");
		printw(0.3*_w, _h - (_h / 2 * 0.9) - 255, -1, "RMB pressed - look around without changing movement direction");
		printw(0.3*_w, _h - (_h / 2 * 0.9) - 280, -1, "LPM - attack");
	}

	void Interface::highscore()
	{
		//odczytaj z notatnika highscore
		printw(0.6*_w, _h - (_h / 2 * 0.3), -1, "HighScore");

		for (int ii = 1; ii <= 10; ++ii)
			printw(0.3*_w, _h - (_h / 2 * 0.3) - (ii)*45, -1, to_string(ii) + ". ");
	}

	void Interface::options()
	{
		select = 0;
	}

	void Interface::credits()
	{
		printw(0.6*_w, _h - (_h / 2 * 0.3), -1, "Created by:");
		printw(0.59*_w, _h - (_h / 2 * 0.3)-90, -1, "Artur Jaworski");
	}

	void Interface::pauseMenu()
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);

		if (select == 255)
			select = 1;
		else if (select > 1)
			select = 0;

		printw(0.47*_w, _h - (_h / 2) + 25 -(select * 45), -1, "___________");

		printw(0.47*_w, _h - (_h / 2)+90, -1, "Game paused");
		printw(0.49*_w, _h - (_h / 2)+30, -1, "Continue");
		printw(0.47*_w, _h - (_h / 2)-15, -1, "Exit to Menu");
	}

#pragma endregion

	int Interface::getState()
	{
		return state;
	}

	#pragma region op overload
	Interface & Interface::operator++()
	{
		++select;
		return *this;
	}

	Interface & Interface::operator--()
	{
		--select;
		return *this;
	}

	Interface Interface::operator++(int)
	{
		Interface tmp = *this;
		++select;
		return tmp;
	}

	Interface Interface::operator--(int)
	{
		Interface tmp = *this;
		--select;
		return tmp;
	}
#pragma endregion

	void Interface::printw(float x, float y, float z, string format) 
	{
		glRasterPos3f(x, y, z);

		for (int i = 0; format[i] != '\0'; i++)
			glutBitmapCharacter(font_style, format[i]);
	}	
#include "../stdafx.h"
#include "Interface.h"

	Interface::Interface() : state(gameState::menu), select(0)
	{
		menu = new Menu("menu", _w, _h);
		options = new Options("options", _w, _h);
		pauseMenu = new PauseMenu("PauseMenu", _w, _h);
		howTo = new HowTo("howTo", _w, _h);
		highscore = new Highscore("highscore", _w, _h);
		credits = new Credits("credits", _w, _h);
		inGame = new Ingame("inGame", _w, _h);
	}

	Interface::~Interface() 
	{
		gameCleanup();

		if (menu != nullptr)
		{
			delete menu;
			menu = nullptr;
		}
		if (options != nullptr)
		{
			delete options;
			options = nullptr;
		}
		if (pauseMenu != nullptr)
		{
			delete pauseMenu;
			pauseMenu = nullptr;
		}
		if (howTo != nullptr)
		{
			delete howTo;
			howTo = nullptr;
		}
		if (highscore != nullptr)
		{
			delete highscore;
			highscore = nullptr;
		}
		if (credits != nullptr)
		{
			delete credits;
			credits = nullptr;
		}
		if (inGame != nullptr)
		{
			delete inGame;
			inGame = nullptr;
		}
	}

	#pragma region menu(UI) control
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
			
				select = 0;
				menu->buttons[3]->active = false;
				menu->buttons[0]->active = true;
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
				//same as menu
				break;
			}
			case gameState::running:
			{
				//minimap?
				break;
			}
			case gameState::pauseMenu:
			{
				if (select == 0)
				{
					state = gameState::running;
					ShowCursor(false);
				}
				else 
				{
					state = gameState::menu;
					gameCleanup();
				}
				select = 0;
			}
		}
	}
#pragma endregion

	//clear active button
	void Interface::buttonClear(int i)
	{
		if (state != gameState::pauseMenu)
		{
			for (int ii = 0; ii < menu->buttons.size(); ++ii)
			{
				if (ii != i)
					menu->buttons[ii]->active = false;
			}
		}
		else
		{
			for (int ii = 0; ii < pauseMenu->buttons.size(); ++ii)
			{
				if (ii != i)
					pauseMenu->buttons[ii]->active = false;
			}
		}
	}

	#pragma region mouse control
	void Interface::mouseClick(const int & x, const int & y)
	{
		switch (state)
		{
			case gameState::menu:
			case gameState::highscore:
			case gameState::credits:
			case gameState::howTo:
			{
			for (int ii = 0; ii < menu->buttons.size(); ++ii)
				if (menu->buttons[ii]->onClick(x, y))
				{
					select = ii;
					buttonClear(ii);
					goNext();
				}
			break;
			}
			case gameState::options:
			{
				//TODO
				break;
			}
			case gameState::pauseMenu:
			{
			for (int ii = 0; ii < pauseMenu->buttons.size(); ++ii)
				if (pauseMenu->buttons[ii]->onClick(x, y))
				{
					select = ii;
					buttonClear(ii);
					goNext();
				}
			}
		}
	}

	void Interface::mouse(const int & x, const int & y)
	{
		switch (state)
		{
			case gameState::menu:
			case gameState::highscore:
			case gameState::credits:
			case gameState::howTo:
			{
			for (int ii = 0; ii < menu->buttons.size(); ++ii)
				if (menu->buttons[ii]->onPointer(x, y))
				{
					select = ii;
					buttonClear(ii);
				}
			break;
			}
			case gameState::options:
			{
				//TODO
				break;
			}
			case gameState::pauseMenu:
			{
			for (int ii = 0; ii < pauseMenu->buttons.size(); ++ii)
				if (pauseMenu->buttons[ii]->onClick(x, y))
				{
					select = ii;
					buttonClear(ii);
				}
			}
		}
	}
#pragma endregion

	void Interface::update()
	{
		_w = glutGet(GLUT_WINDOW_WIDTH);
		_h = glutGet(GLUT_WINDOW_HEIGHT);
		
		 UIinit();
		
		switch (state)
		{
			case gameState::menu:
			{
				menu->render(_w, _h);
				break;
			}
			case gameState::howTo:
			{
				menu->render(_w, _h);
				howTo->render(_w, _h);
				break;
			}
			case gameState::highscore:
			{
				menu->render(_w, _h);
				highscore->render(_w, _h);
				break;
			}
			case gameState::credits:
			{
				menu->render(_w, _h);
				credits->render(_w, _h);
				break;
			}
			case gameState::options:
			{
				options->render(_w, _h);
				break;
			}
			case gameState::pauseMenu:
			{
				pauseMenu->render(_w, _h);
				break;
			}
			case gameState::running:
			{
				if (game != nullptr && getState() == gameState::running)
				{
					inGame->render(_w, _h, game->player->score, game->player->ammo, game->player->hp);
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

	#pragma region init & cleanUp game
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

	void Interface::gameCleanup()
	{
		if (game != nullptr)
		{
			delete game;
			game = nullptr;
		}
	}
#pragma endregion

	int Interface::getState()
	{
		return state;
	}

	#pragma region op overload
	Interface & Interface::operator++()
	{
		if (state != gameState::pauseMenu)
		{
			menu->buttons[select]->active = false;
			++select;
			if (select >= menu->buttons.size())
				select = 0;
			menu->buttons[select]->active = true;
		}
		else
		{
			pauseMenu->buttons[select]->active = false;
			++select;
			if (select >= pauseMenu->buttons.size())
				select = 0;
			pauseMenu->buttons[select]->active = true;
		}
		return *this;
	}

	Interface & Interface::operator--()
	{
		if (state != gameState::pauseMenu)
		{
			menu->buttons[select]->active = false;
			--select;
			if (select == 255)
				select = 5;
			menu->buttons[select]->active = true;
		}
		else
		{
			pauseMenu->buttons[select]->active = false;
			--select;
			if (select == 255)
				select = 1;
			pauseMenu->buttons[select]->active = true;
		}
		return *this;
	}

	Interface Interface::operator++(int)
	{
		Interface tmp = *this;

		if (state != gameState::pauseMenu)
		{
			menu->buttons[select]->active = false;
			++select;
			if (select >= menu->buttons.size())
				select = 0;
			menu->buttons[select]->active = true;
		}
		else
		{
			pauseMenu->buttons[select]->active = false;
			++select;
			if (select >= pauseMenu->buttons.size())
				select = 0;
			pauseMenu->buttons[select]->active = true;
		}
		return tmp;
	}

	Interface Interface::operator--(int)
	{
		Interface tmp = *this;
		if (state != gameState::pauseMenu)
		{
			menu->buttons[select]->active = false;
			--select;
			if (select == 255)
				select = 5;
			menu->buttons[select]->active = true;
		}
		else
		{
			pauseMenu->buttons[select]->active = false;
			--select;
			if (select == 255)
				select = 1;
			pauseMenu->buttons[select]->active = true;
		}
		return tmp;
	}
#pragma endregion
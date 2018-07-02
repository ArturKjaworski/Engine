#include "stdafx.h"
#include "Game.h"

int _width(920);
int _height(640);

Game* game = nullptr;

#pragma region light vars
GLfloat lightAmb[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat lightDif[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat lightSpec[] = { 1.0, 1.0, 1.0, 1 };
GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float l_pos1[] = {0,300,0,1};
#pragma endregion

bool down = false;      //bool for (not)pressed RMB button check

void init()
{
#pragma region enable
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#pragma endregion

	if (game ==nullptr)
		game = new Game();
	else
	{
		delete game;
		game = nullptr;
		game = new Game();
	}
	glutWarpPointer(_width / 2, _height / 2);
	ShowCursor(false);
}

void help()
{
	system("cls");
	cout << "1: create PickUp Obj\n";
	cout << "2: create Interct Obj\n";

	cout << "w,s,a,d: movement\n";
	cout << "z,x: zoom in/out\n";
	cout << "\nMouse:\nhold RMB to looking around\nwithout anu btn: move in that direction\n";
	cout << "LMB to interact (not working for now)\n";

	cout << "q: exit\n";
}

void render()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (game !=nullptr)
		game->update();

#pragma region Light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, l_pos1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpec);
	glMateriali(GL_FRONT, GL_SHININESS, 10);
#pragma endregion

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)w / h, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	_width = w;
	_height = h;
}

void keyboard(unsigned char key, int x, int y)
{
	PX_UNUSED(x);
	PX_UNUSED(y);
	int state = glutGetModifiers();
	switch (state)
	{
	case GLUT_ACTIVE_SHIFT:
		game->player->setState(Player::run);
		break;
	case GLUT_ACTIVE_CTRL:
		game->player->setState(Player::crouch);
		break;
	default:
		game->player->setState(Player::walk);
		break;
	}

	switch (key)
	{

#pragma region player control
	case 'w': case 'W':
		game->player->move(Player::front);
		break;

	case 's':case 'S':
		game->player->move(Player::back);
		break;

	case 'a':case 'A':
		game->player->move(Player::left);
		break;

	case 'd':case 'D':
		game->player->move(Player::right);
		break;

	case 32:
		//jump
		break;

	case 'x':
		game->player->zoom('+');
		break;
	case 'z':
		game->player->zoom('-');
		break;
#pragma endregion

	case 'Q':
	case 'q':
	case 27:
		exit(0);

	default:
		help();
		break;
	}
}

#pragma region mouse funcs
//tracking mouse buttons
void mouse(int but, int state, int x, int y)
{
	PX_UNUSED(x);
	PX_UNUSED(y);
	if (but == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		down = true;

	if (but == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		game->player->setForward();
		down = false;
	}
	if (but == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		cout << "interact" << endl;
}
//look around
void mouseMove(int x, int y)
{
	if (down)
		game->player->mouse(x - width / 2, y - height / 2);
}
//move in that direction
void passiveMouseMove(int x, int y)
{
	game->player->look(x - width / 2, y - height / 2);
}
#pragma endregion

void timer(int val)
{
	render();
	glutTimerFunc(val, timer, 0);
}

// atexit func
void ex()
{
	if (game != nullptr)
	{
		delete game;
		game = nullptr;
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	help();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(_width, _height);
	glutInitWindowPosition(1920 - _width, 1080 - _height);
	glutCreateWindow("Another PacMan?");

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(passiveMouseMove);

	glutTimerFunc(1000 / FPS, timer, 0);

	atexit(ex);
	init();
	glutMainLoop();
	
	return 0;
}
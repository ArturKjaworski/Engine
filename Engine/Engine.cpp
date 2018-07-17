#include "stdafx.h"
#include "graphics classes/Interface.h"

int _width(920);
int _height(640);

Interface* inter=nullptr;

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

	if (inter == nullptr)
		inter = new Interface();
	else
	{
		delete inter;
		inter = nullptr;
		inter = new Interface();
	}
}

void render()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	#pragma region Light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, l_pos1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpec);
	glMateriali(GL_FRONT, GL_SHININESS, 10);
#pragma endregion

	inter->update();
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
	if (inter->game != nullptr)
	{
		switch (state)
		{
		case GLUT_ACTIVE_SHIFT:
			inter->game->player->setState(Player::run);
			break;
		case GLUT_ACTIVE_CTRL:
			inter->game->player->setState(Player::crouch);
			break;
		default:
			inter->game->player->setState(Player::walk);
			break;
		}
	}

	switch (key)
	{
#pragma region user control
	case 'w': case 'W':
	{
		if (inter->getState() == Interface::gameState::running)
			inter->game->player->move(Player::front);
		else
			--(*inter);
		break;
	}

	case 's':case 'S':
	{
		if (inter->getState() == Interface::gameState::running)
			inter->game->player->move(Player::back);
		else
			++(*inter);
		break;
	}

	case 'a':case 'A':
		if (inter->getState() == Interface::gameState::running)
			inter->game->player->move(Player::left);
		break;

	case 'd':case 'D':
		if (inter->getState() == Interface::gameState::running)
			inter->game->player->move(Player::right);
		break;

	case 'x':
		if (inter->getState() == Interface::gameState::running)
			inter->game->player->zoom('+');
		break;

	case 'z':
		if (inter->getState() == Interface::gameState::running)
			inter->game->player->zoom('-');
		break;
#pragma endregion

	case 32:
	case 13:
		inter->goNext();
		break;

	case 27:
		inter->goBack();
		break;

	default:
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
		inter->game->player->setForward();
		down = false;
	}
	if (but == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (inter->getState() == Interface::gameState::running)
			cout << "interact" << endl;
	}
}
//look around
void mouseMove(int x, int y)
{
	if (down)
		if (inter->getState() == Interface::gameState::running)
			inter->game->player->mouse(x - width / 2, y - height / 2);
}
//move in that direction
void passiveMouseMove(int x, int y)
{
	if (inter->getState() == Interface::gameState::running)
		inter->game->player->look(x - width / 2, y - height / 2);
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
	if (inter != nullptr)
	{
		delete inter;
		inter = nullptr;
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(_width, _height);
	glutInitWindowPosition(0,0);
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